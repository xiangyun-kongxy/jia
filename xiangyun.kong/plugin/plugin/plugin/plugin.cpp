//
// Created by xiangyun.kong on 8/8/16.
//

#include "plugin.h"

#include <pthread.h>

#include <lib/identifier/id_name.h>

#include <plugin/manager/plugin_manager.hpp>
#include <plugin/response/simple_response.h>
#include <plugin/event/simple_event.h>

#include <errors.h>

#include <iostream>

using namespace kxy;
using namespace std;

namespace pf {
    
    ptr<plugin> g_lifecycle = nullptr;
    ptr<plugin> g_bus = nullptr;
    
    void plugin::on_event(ptr<event> evt) {
        ptr<trigger> trigger = nullptr;
        if (evt != nullptr) {
            trigger = m_triggers[evt->name()];
            if (trigger != nullptr)
                trigger->happen(this, evt);
        }
    }

    ptr<response> plugin::do_task(ptr<event> evt) {
        ptr<executor> executor = nullptr;
        if (evt != nullptr) {
            executor = m_executors[evt->name()];
            if (executor != nullptr)
                return executor->run(this, evt);
        }
        return new simple_response(evt, EC_TASK_NOT_SUPPORTED,
                                   EM_TASK_NOT_SUPPORTED);
    }

    list<ptr<identifier>> plugin::depend_on() const {
        return list<ptr<identifier>>();
    }

    void plugin::init() {
        
    }
    
    void plugin::uninit() {
        
    }
    
    list<ptr<identifier>> plugin::supported_event() const {
        list<ptr<identifier>> evt;
        map<string,ptr<trigger>>::const_iterator i;
        for(i = m_triggers.begin(); i != m_triggers.end(); ++i)
            evt.push_back(new id_name(i->first));
        
        
        map<string,ptr<executor>>::const_iterator it;
        for(it = m_executors.begin(); it != m_executors.end(); ++it)
            evt.push_back(new id_name(it->first));
        
        return evt;
    }

    ptr<plugin> plugin::current_plugin() {
        plugin_manager* manager = plugin_manager::instance();
        context_info ci = manager->get_context_by_thread_id(pthread_self());
        return ci.plugin;
    }
    
    ptr<object> plugin::current_task() {
        plugin_manager* manager = plugin_manager::instance();
        context_info ci = manager->get_context_by_thread_id(pthread_self());
        return ci.task;
    }

}
