//
//  plugin_manager.cpp
//  plugin
//
//  Created by xiangyun.kong on 10/3/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "plugin_manager.hpp"
#include "function_manager.hpp"
#include "dependence_manager.hpp"

#include <lib/lock/auto_lock.h>

namespace pf {

    plugin_manager* g_plugin_manager = nullptr;
    
    void __attribute__((constructor)) __init_plugin_manager() {
        g_plugin_manager = new plugin_manager;
    }

    plugin_manager* plugin_manager::instance() {
        return g_plugin_manager;
    }
    
    plugin_manager::plugin_manager() {
        pthread_mutex_init(&m_mutex, nullptr);
    }
    
    void plugin_manager::add_plugin(ptr<plugin> pl) {
        auto_lock _(&m_mutex);

        list<plugin_info>::iterator i;
        i = find(m_plugins.begin(), m_plugins.end(), pl);
        if (i == m_plugins.end()) {
            plugin_info pi;
            pi.pl = pl;
            pi.is_active = false;
            pi.threads.push_back(_create_thread(pl));
            m_plugins.push_back(pi);

            for (ptr<identifier> function : pl->accepted_event()) {
                function_manager::instance()->add_function(pl, function);
            }
            for (ptr<identifier> function : pl->accepted_task()) {
                function_manager::instance()->add_function(pl, function);
            }
            for (ptr<identifier> obj : pl->depend_on()) {
                dependence_manager::instance()->add_depend(pl, obj);
            }
        }
    }

    void plugin_manager::rm_plugin(ptr<identifier> id) {
        auto_lock _(&m_mutex);

        if (!dependence_manager::instance()->is_depended(id)) {
            list<plugin_info>::iterator i;
            i = find(m_plugins.begin(), m_plugins.end(), id);
            if (i != m_plugins.end()) {
                ptr<plugin> pl = (*i).pl;
                for (ptr<identifier> function : pl->accepted_task()) {
                    function_manager::instance()->rm_function(function);
                }
                for (ptr<identifier> function : pl->accepted_event()) {
                    function_manager::instance()->rm_function(function);
                }
                for (ptr<identifier> obj : pl->depend_on()) {
                    dependence_manager::instance()->rm_depend(pl, obj);
                }

                m_plugins.erase(i);
            }
        }
    }

    const plugin_info* plugin_manager::find_plugin(ptr<identifier> id) {
        auto_lock _(&m_mutex);
        
        list<plugin_info>::iterator i;
        i = find(m_plugins.begin(), m_plugins.end(), id);
        if (i != m_plugins.end()) {
            return &*i;
        }
        return nullptr;
    }

    list<plugin_info> plugin_manager::get_all_plugin() {
        auto_lock _(&m_mutex);

        return m_plugins;
    }

    void plugin_manager::active_plugin(ptr<identifier> id) {
        auto_lock _(&m_mutex);

        if (dependence_manager::instance()->is_depend_ready(id)) {
            list<plugin_info>::iterator i;
            i = find(m_plugins.begin(), m_plugins.end(), id);
            if (i != m_plugins.end()) {
                for (ptr<plugin_thread> thread : (*i).threads) {
                    thread->start();
                }

                for (ptr<identifier> function : (*i).pl->accepted_task()) {
                    function_manager::instance()->active_function(function);
                }

                for (ptr<identifier> function : (*i).pl->accepted_event()) {
                    function_manager::instance()->active_function(function);
                }

                (*i).is_active = true;
            }
        }
    }
    
    void plugin_manager::suspend_plugin(ptr<identifier> id) {
        auto_lock _(&m_mutex);

        if (!dependence_manager::instance()->is_depended(id)) {
            list<plugin_info>::iterator i;
            i = find(m_plugins.begin(), m_plugins.end(), id);
            if (i != m_plugins.end()) {
                for (ptr<identifier> function : (*i).pl->accepted_task()) {
                    function_manager::instance()->suspend_function(function);
                }

                for (ptr<identifier> function : (*i).pl->accepted_event()) {
                    function_manager::instance()->suspend_function(function);
                }

                for (ptr<plugin_thread> thread : (*i).threads) {
                    thread->pause();
                }

                (*i).is_active = false;
            }
        }
    }

    const plugin_info*
    plugin_manager::get_plugin_by_thread_id(pthread_t thread_id) {
        auto_lock _(&m_mutex);

        list<plugin_info>::iterator i;
        i = find(m_plugins.begin(), m_plugins.end(), thread_id);
        if (i != m_plugins.end()) {
            return &*i;
        }
        return nullptr;
    }


    bool plugin_manager::check_ready(ptr<kxy::identifier> id)  {
        auto_lock _(&m_mutex);

        list<plugin_info>::iterator i;
        i = find(m_plugins.begin(), m_plugins.end(), id);
        if (i != m_plugins.end()) {
            return (*i).is_active;
        }
        return false;
    }

    ptr<plugin_thread> plugin_manager::_create_thread(ptr<plugin> pl) {
        ptr<cqueue<ptr<object>>> pool = new cqueue<ptr<object>>;
        ptr<plugin_thread> thread = new plugin_thread(pool, pl);
        return thread;
    }
}
