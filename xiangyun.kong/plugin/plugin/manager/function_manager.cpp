//
//  function_manager.cpp
//  plugin
//
//  Created by xiangyun.kong on 10/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "function_manager.hpp"
#include "dependence_manager.hpp"

#include <lib/lock/auto_lock.h>

namespace pf {

    function_manager* g_function_manager = nullptr;

    void __attribute__((constructor)) __init_function_manager() {
        g_function_manager = new function_manager;
    }

    function_manager* function_manager::instance() {
        return g_function_manager;
    }

    function_manager::function_manager() {
        pthread_mutex_init(&m_mutex, nullptr);
    }

    void function_manager::add_function(ptr<plugin> owner,
                                        ptr<identifier> function) {
        auto_lock _(&m_mutex);
        
        list<function_info>::iterator i;
        i = find(m_functions.begin(), m_functions.end(), function);
        if (i == m_functions.end()) {
            function_info fi;
            fi.function = function;
            fi.is_active = false;
            fi.provider = owner;
            m_functions.push_back(fi);
        }
    }

    void function_manager::rm_function(ptr<identifier> function) {
        auto_lock _(&m_mutex);

        if (!dependence_manager::instance()->is_depended(function)) {
            list<function_info>::iterator i;
            i = find(m_functions.begin(), m_functions.end(), function);
            if (i != m_functions.end()) {
                m_functions.erase(i);
            }
        }
    }

    void function_manager::active_function(ptr<identifier> function) {
        auto_lock _(&m_mutex);

        list<function_info>::iterator i;
        i = find(m_functions.begin(), m_functions.end(), function);
        if (i != m_functions.end()) {
            (*i).is_active = true;
        }
    }

    void function_manager::suspend_function(ptr<identifier> function) {
        auto_lock _(&m_mutex);

        if (!dependence_manager::instance()->is_depended(function)) {
            list<function_info>::iterator i;
            i = find(m_functions.begin(), m_functions.end(), function);
            if (i != m_functions.end()) {
                (*i).is_active = false;
            }
        }
    }

    bool function_manager::check_ready(ptr<kxy::identifier> id) {
        auto_lock _(&m_mutex);

        list<function_info>::iterator i;
        i = find(m_functions.begin(), m_functions.end(), id);
        if (i != m_functions.end()) {
            return (*i).is_active;
        }
        
        return false;
    }
}

