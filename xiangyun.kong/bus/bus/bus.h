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
        ptr<object> wait_object(ptr<identifier> obj, timeval& timeout);
        void set_waiting(ptr<identifier> id);
        void set_object(ptr<object> obj);

        void set_event_trigger(ptr<identifier> evt, task_callback func);
        
    private:
        pthread_mutex_t m_mutex;
        mutex m_trigger_mutex;
        pthread_cond_t m_changed;

        map<ptr<identifier>, ptr<object>> m_waiting;

        map<ptr<identifier>, task_callback> m_user_trigger;
    };
    
}

#endif //PLUGIN_BUS_H
