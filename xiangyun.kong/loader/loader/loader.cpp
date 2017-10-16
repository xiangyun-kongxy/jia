/*
 *  loader.cpp
 *  loader
 *
 *  Created by 孔祥云 on 12/31/16.
 *  Copyright © 2016 孔祥云. All rights reserved.
 *
 */

#include "loader.hpp"
#include <plugin/plugin.h>
#include <bus/bus/bus.h>
#include <lifecycle/src/lifecycle.hpp>
#include <task/simple_task.h>
#include <manager/plugin_manager.hpp>
#include <identifier/id_name.h>
#include <functions.h>

using namespace kxy;
namespace pf {
    
    extern ptr<plugin> g_lifecycle;
    extern ptr<plugin> g_bus;
    
    loader::loader(const string& conf_path) {
        m_plugin_conf_path = conf_path;
        g_lifecycle = new lifecycle();
        g_bus = new bus();
        plugin_manager::instance()->add_plugin(g_lifecycle);
        plugin_manager::instance()->add_plugin(g_bus);
    }
    
    void loader::load() {
        if(g_lifecycle != nullptr) {
            call_plugin(new id_name(g_lifecycle->name()), F_LOAD_PLUGIN,
                        m_plugin_conf_path);
        }
    }

}
