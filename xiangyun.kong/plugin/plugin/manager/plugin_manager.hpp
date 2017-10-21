//
//  plugin_manager.hpp
//  plugin
//
//  Created by xiangyun.kong on 10/3/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef plugin_manager_hpp
#define plugin_manager_hpp

#include <stdio.h>

#include <lib/object/object.h>
#include <plugin/plugin/plugin.h>

#include "plugin_thread.hpp"
#include "help_thread.hpp"

#include <mutex>

using namespace kxy;
using namespace std;

namespace pf {
    
    struct context_info {
        ptr<plugin> plugin;
        ptr<object> task;
    };
    
    struct plugin_info {
        ptr<plugin> pl;
        bool is_active;
        list<ptr<plugin_thread>>* threads;
        
        bool operator == (const ptr<plugin>& p) {
            return pl == p;
        }
        
        bool operator == (const ptr<identifier>& id) {
            return id->match(pl);
        }

        bool operator == (pthread_t thread_id) {
            for (ptr<plugin_thread> thread : *threads) {
                if (thread->thread_id() == thread_id) {
                    return true;
                }
            }
            return false;
        }
    };
    
    class plugin_manager {
    private:
        friend void __init_plugin_manager();
        friend void __uninit_plugin_manager();
        plugin_manager();
        ~plugin_manager();

    public:
        static plugin_manager* instance();

    public:
        void add_plugin(ptr<plugin> p);
        void rm_plugin(ptr<identifier> id);
        void active_plugin(ptr<identifier> id);
        void suspend_plugin(ptr<identifier> id);

        bool check_ready(ptr<identifier> id);
        
        list<plugin_info*> get_all_plugin();
        const plugin_info* find_plugin(ptr<identifier> id);
        context_info get_context_by_thread_id(pthread_t thread_id);

    private:
        ptr<plugin_thread> _create_thread(ptr<plugin>);

    private:
        list<plugin_info*> m_plugins;
        list<ptr<help_thread>> m_task_helper;
        map<pthread_t, ptr<thread>> m_threads;

    };
}

#endif /* plugin_manager_hpp */
