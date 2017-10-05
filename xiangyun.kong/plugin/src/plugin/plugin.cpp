//
// Created by xiangyun.kong on 8/8/16.
//

#include "plugin.h"
#include "../manager/plugin_manager.hpp"
#include <response/simple_response.h>
#include <identifier/id_name.h>
#include <event/simple_event.h>
#include <pthread.h>
#include <constants.h>
#include <task/simple_task.h>

using namespace kxy;

namespace pf {
    
    ptr<plugin> g_lifecycle = nullptr;
    ptr<plugin> g_bus = nullptr;
    
    void plugin::on_event(ptr<event> evt) {
        ptr<trigger> trigger = nullptr;
        if (evt != nullptr) {
            if (evt->type() == "simple_event")
                trigger = m_event_processor[((ptr<simple_event>)evt)->event_type()];
            else
                trigger = m_event_processor[evt->type()];
        }
        if (trigger != nullptr)
            trigger->occur(this, evt);
    }

    ptr<response> plugin::do_task(ptr<task> tsk) {
        ptr<executor> executor = nullptr;
        if (tsk != nullptr) {
            if(tsk->is_kind_of("simple_task"))
                executor = m_task_processor[((ptr<simple_task>)tsk)->task_name()];
            else
                executor = m_task_processor[tsk->type()];
        }
        if (executor != nullptr)
            return executor->run(this, tsk);
        else
            return new simple_response(EC_TASK_NOT_SUPPORTED, EM_TASK_NOT_SUPPORTED);
    }

    list<ptr<identifier>> plugin::depend_on() const {
        return list<ptr<identifier>>();
    }

    list<ptr<identifier>> plugin::accepted_event() const {
        list<ptr<identifier>> evt;
        map<string,ptr<trigger>>::const_iterator i;
        for(i = m_event_processor.begin(); i != m_event_processor.end(); ++i)
            evt.push_back(new id_name(i->first));
        return evt;
    }

    list<ptr<identifier>> plugin::accepted_task() const {
        list<ptr<identifier>> tsk;
        map<string,ptr<executor>>::const_iterator i;
        for(i = m_task_processor.begin(); i != m_task_processor.end(); ++i)
            tsk.push_back(new id_name(i->first));
        return tsk;
    }

    ptr<plugin> plugin::current_plugin() {
        ptr<plugin_manager> manager = plugin_manager::instance();
        return manager->get_plugin_by_thread_id(pthread_self());
    }

    string plugin::type() const {
        return "plugin";
    }
    
    bool plugin::is_kind_of(const string &type_name) const {
        return type_name == "plugin" || object::is_kind_of(type_name);
    }

}
