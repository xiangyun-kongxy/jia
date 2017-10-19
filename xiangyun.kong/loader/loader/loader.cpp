/*
 *  loader.cpp
 *  loader
 *
 *  Created by 孔祥云 on 12/31/16.
 *  Copyright © 2016 孔祥云. All rights reserved.
 *
 */

#include "loader.hpp"

#include <lib/identifier/id_name.h>

#include <plugin/plugin/plugin.h>
#include <plugin/task/simple_task.h>
#include <plugin/manager/plugin_manager.hpp>

#include <bus/bus.h>

#include <lifecycle/lifecycle.hpp>

#include <events.h>

using namespace kxy;
namespace pf {
    
    extern ptr<plugin> g_lifecycle;
    extern ptr<plugin> g_bus;
    
    loader::loader(const string& conf_path) {
        m_plugin_conf_path = conf_path;
        g_lifecycle = new lifecycle();
        g_bus = new bus();

        plugin_manager* pm = plugin_manager::instance();

        pm->add_plugin(g_lifecycle);
        pm->add_plugin(g_bus);
        pm->active_plugin(new id_name(g_bus->name()));
        pm->active_plugin(new id_name(g_lifecycle->name()));
    }
    
    void loader::load() {
        if(g_lifecycle != nullptr) {
            send_to(new id_name(g_lifecycle->name()), EVT_START_FRAMEWORK,
                    m_plugin_conf_path);
        }
    }

}

