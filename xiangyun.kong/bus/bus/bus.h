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
        
    public:
        void hold_object(ptr<identifier> obj);
        void release_object(ptr<identifier> obj);

        ptr<object> wait_object(ptr<identifier> obj);
        void set_object(ptr<object> obj);

        void set_event_trigger(ptr<identifier> evt, task_callback func);
        
    public:
        virtual string type() const override ;
        virtual bool is_kind_of(const string &type_name) const override ;
        
    private:
        pthread_mutex_t m_mutex;
        pthread_cond_t m_changed;

        list<ptr<identifier>> m_waiting_object;
        list<ptr<object>> m_object_set;

        set<ptr<identifier>> m_hold_object;

        map<ptr<identifier>, task_callback> m_user_trigger;
    };
    
}

#endif //PLUGIN_BUS_H
