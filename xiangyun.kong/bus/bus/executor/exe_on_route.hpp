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

#include <plugin/manager/plugin_manager.hpp>

#include <bus/bus.hpp>
#include <bus/schedule/event_router/router.hpp>

#include <log.hpp>

using namespace std;

namespace pf {
    
    class on_route : public executor {
    public:
        DECLARE_TYPE(executor, EXE_ON_ROUTE)
        
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
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
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

            char log_buf[128];
            snprintf(log_buf, 128, "%-20s %16s -> %-16s", evt->name().c_str(),
                     evt->deliver()->name().c_str(),
                     evt->destination()->name().c_str());
            info_log("bus", log_buf);

            return nullptr;
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
