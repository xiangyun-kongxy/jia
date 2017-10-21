//
//  simple_task.cpp
//  plugin
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include "simple_task.h"
#include <lib/identifier/id_any.h>
#include <plugin/plugin/plugin.h>

using namespace kxy;

namespace pf {

    class terminal : public plugin {
    public:
        DECLARE_TYPE(plugin, "terminal");
    };

    ptr<terminal> g_terminal = new terminal;
    
    simple_task::simple_task(const string& task_name) :
    simple_task::simple_task(task_name, (ptr<serializable>)nullptr) {
        
    }
    
    simple_task::simple_task(const string& task_name, ptr<serializable> param) :
    simple_task::simple_task(task_name, param, new id_any()){
    
    }
    
    simple_task::simple_task(const string& task_name, ptr<identifier> proc) :
    simple_task::simple_task(task_name, nullptr, proc) {
    
    }
    
    simple_task::simple_task(const string& task_name, ptr<serializable> param,
                             ptr<identifier> proc) {
        m_caller = plugin::current_plugin();
        m_task_name = task_name;
        m_param = param;
        m_processor = proc;

        if (m_caller == nullptr) {
            m_caller = g_terminal;
        }
    }
    
    simple_task::simple_task(const string& task_name, ptr<plugin> caller) {
        m_task_name = task_name;
        m_param = nullptr;
        m_processor = nullptr;
        m_caller = caller;

        if (m_caller == nullptr) {
            m_caller = g_terminal;
        }
    }
    
    ptr<plugin> simple_task::caller() const {
        return m_caller;
    }
    
    ptr<identifier> simple_task::processor() const {
        return m_processor;
    }
    
    ptr<serializable> simple_task::param() const {
        return m_param;
    }
    
    string simple_task::task_name() const {
        return m_task_name;
    }
    
}
