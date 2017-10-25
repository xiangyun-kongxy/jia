//
// Created by 孔祥云 on 8/10/16.
//

#ifndef PLUGIN_BUS_H
#define PLUGIN_BUS_H

#include <sys/semaphore.h>
#include <pthread.h>
#include <set>

#include <lib/object/ptr.h>

#include <plugin/plugin/plugin.h>

#include <bus/trigger/trigger_on_route.h>

#include <ipc.hpp>

using namespace std;
using namespace kxy;

namespace pf {
    
    class bus : public plugin {
    public:
        bus();
        virtual ~bus();
        DECLARE_TYPE(plugin, PLUGIN_BUS);
        
    public:
        virtual void on_event(ptr<event> evt) override;
        virtual ptr<response> do_task(ptr<event> evt) override;

    public:
        void add_waiting_object(ptr<identifier> id);
        void add_object(ptr<object> obj);
        ptr<object> wait_object(ptr<identifier> obj, timeval& timeout);

        void add_rsp_trigger(ptr<event> evt, fcallback func);
        void add_response(ptr<response> rsp);
        ptr<response> wait_response(ptr<event> evt, timeval& timeout);
        
    private:
        bool __is_timeout(const timeval& timeout);
        
    private:
        pthread_mutex_t m_obj_mutex;
        map<ptr<identifier>, ptr<object>> m_waiting_objects;
        pthread_cond_t m_obj_changed;

        pthread_mutex_t m_rsp_mutex;
        map<ptr<event>, fcallback> m_rsp_trigger;
        map<ptr<event>, ptr<response>> m_rsps;
        pthread_cond_t m_rsp_changed;
        
        on_route* m_router;
    };
    
}

#endif //PLUGIN_BUS_H
