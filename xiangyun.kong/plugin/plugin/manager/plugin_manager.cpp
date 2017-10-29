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

#include <lib/init/initializer.hpp>

#include <iostream>

using namespace std;
using namespace kxy;

namespace pf {

    recursive_mutex g_plugin_managing_mutex;
    plugin_manager* g_plugin_manager = nullptr;

#define HELP_THREAD_COUNT   8
    
    void __uninit_plugin_manager() {
        delete g_plugin_manager;
        g_plugin_manager = nullptr;
    }
    
    void __attribute__((constructor)) __init_plugin_manager() {
        g_plugin_manager = new plugin_manager;
        
        register_uninitializer("uninitialize plugin manager", __uninit_plugin_manager);
    }

    plugin_manager* plugin_manager::instance() {
        return g_plugin_manager;
    }
    
    plugin_manager::plugin_manager() {
        m_version = 1;
    }
    
    plugin_manager::~plugin_manager() {
        ++m_version;
    }
    
    void plugin_manager::add_plugin(ptr<plugin> pl) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        if (m_plugins.find(pl) == m_plugins.end()) {
            m_plugins.insert(pl);

            for (ptr<function> function : pl->supported_functions()) {
                function_manager::instance()->add_function(pl, function);
            }
            for (ptr<identifier> obj : pl->depend_on()) {
                dependence_manager::instance()->add_depend(pl, obj);
            }
            
            ++m_version;
        } else {
            cout << "error: plugin " << pl->name() << " duplicated." << endl;
        }
    }

    void plugin_manager::rm_plugin(ptr<plugin> pl) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        if (m_plugins.find(pl) != m_plugins.end()) {
            for (ptr<function> function : pl->supported_functions()) {
                function_manager::instance()->rm_function(function);
            }
            for (ptr<identifier> obj : pl->depend_on()) {
                dependence_manager::instance()->rm_depend(pl, obj);
            }

            m_plugins.erase(pl);
            ++m_version;
        }
    }

    ptr<plugin> plugin_manager::find_plugin(ptr<identifier> id) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);
        
        set<ptr<plugin>>::iterator i;
        for (i = m_plugins.begin(); i != m_plugins.end(); ++i) {
            if (id->match(*i))
                break;
        }
        
        if (i != m_plugins.end()) {
            return *i;
        } else {
            return nullptr;
        }
    }

    list<ptr<plugin>> plugin_manager::get_all_plugin() {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);
        
        list<ptr<plugin>> result(m_plugins.begin(), m_plugins.end());
        return result;
    }

    void plugin_manager::plugin_actived(ptr<pf::plugin> pl) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        for (ptr<function> function : pl->supported_functions()) {
            function_manager::instance()->active_function(function);
        }

        ++m_version;
    }
    
    void plugin_manager::plugin_suspended(ptr<pf::plugin> pl) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        for (ptr<function> function : pl->supported_functions()) {
            function_manager::instance()->suspend_function(function);
        }

        ++m_version;
    }

    long plugin_manager::version() const {
        return m_version;
    }

    bool plugin_manager::is_actived(ptr<kxy::identifier> id) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        ptr<plugin> pl = find_plugin(id);
        return pl != nullptr && pl->status() == PS_RUNNING;
    }

    bool plugin_manager::has_task(ptr<kxy::identifier> id) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        ptr<plugin> pl = find_plugin(id);
        if (pl != nullptr) {
            return pl->tasks()->size() > 0;
        } else {
            return false;
        }
            
    }
    
}
