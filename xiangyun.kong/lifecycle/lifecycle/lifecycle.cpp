//
//  lifecycle.cpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include "lifecycle.hpp"
#include "executor/exe_start_framework.hpp"
#include "executor/exe_stop_framework.hpp"
#include "executor/exe_load_plugin.hpp"
#include "executor/exe_unload_plugin.hpp"

#include <plugin/manager/thread_manager.hpp>
#include <plugin/plugin/plugin_config.hpp>

#include <class_names.hpp>
#include <messages.hpp>

#include <iostream>

using namespace std;

namespace pf{
    
    lifecycle::lifecycle() {
        m_executors[M_START_FRAMEWORK] = new start_framework;
        m_executors[M_STOP_FRAMEWORK]  = new stop_framework;
        m_executors[M_LOAD_PLUGIN]     = new load_plugin;
        m_executors[M_UNLOAD_PLUGIN]   = new unload_plugin;
    }

    lifecycle::~lifecycle() {
        map<char*, list<plugin_config*>>::iterator i;
        for (i = m_configs.begin(); i != m_configs.end(); ++i) {
            delete[] i->first;

            for (plugin_config* conf : i->second) {
                delete conf;
            }
        }
    }

    void lifecycle::init() {
        plugin::init();

        thread_manager* tm = thread_manager::instance();
        tm->enable_help_thread(this);
    }
    
    void lifecycle::set_config(char* buf, const list<plugin_config*>& configs) {
        m_configs[buf] = configs;
    }

}
