/**
 * copyright @2016. all rights reserved.
 *
 * @since:  11:01 PM 8/10/16
 * @author: xiangyun kong
 *
 * description:
 *
 */

#ifndef PLUGIN_TRG_ON_ROUTING_EVENT_H
#define PLUGIN_TRG_ON_ROUTING_EVENT_H

#include <plugin/trigger/trigger.hpp>
#include <plugin/event/event.hpp>

#include <plugin/manager/plugin_manager.hpp>

#include <bus/bus.hpp>
#include <bus/schedule/event_router/router.hpp>

#include <log.hpp>

#include <iostream>

using namespace std;

namespace pf {
    
    class on_route : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_ON_ROUTE);
        
    public:
        on_route() {
            pthread_key_create(&m_sheduler, _release_scheduler);
            pthread_key_create(&m_version, nullptr);
        }
        
        ~on_route() {
            pthread_key_delete(m_version);
            pthread_key_delete(m_sheduler);
        }
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            router* rt = (router*)pthread_getspecific(m_sheduler);
            if (rt == nullptr) {
                rt = new router;
                pthread_setspecific(m_sheduler, rt);
            }
            
            long version = (long)pthread_getspecific(m_version);
            if (version != plugin_manager::instance()->version()) {
                rt->update_plugins();
                version = plugin_manager::instance()->version();
                pthread_setspecific(m_version, (void*)version);
            }
            
            rt->schedule(evt);
            
            info_log("bus", evt->name() + " " +
                     evt->deliver()->name() + " -> " +
                     evt->destination()->name());
        }
        
    private:
        static void _release_scheduler(void* param) {
            router* r = (router*)param;
            delete r;
        }
        
    private:
        pthread_key_t m_sheduler;
        pthread_key_t m_version;
    };
    
}

#endif //PLUGIN_TRG_ON_ROUTING_EVENT_H
