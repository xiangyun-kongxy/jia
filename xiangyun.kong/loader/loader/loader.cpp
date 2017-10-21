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
#include <lib/init/initializer.hpp>

#include <plugin/plugin/plugin.h>
#include <plugin/task/simple_task.h>
#include <plugin/manager/plugin_manager.hpp>

#include <bus/bus.h>

#include <lifecycle/lifecycle.hpp>

#include <events.h>
#include <names.h>


using namespace kxy;
namespace pf {
    
    extern ptr<plugin> g_lifecycle;
    extern ptr<plugin> g_bus;
    
    void loader::load(const string& conf_path) {
        g_lifecycle = new lifecycle();
        g_bus = new bus();

        plugin_manager* pm = plugin_manager::instance();
        pm->add_plugin(g_lifecycle);
        pm->add_plugin(g_bus);
        pm->active_plugin(new id_name(PLUGIN_BUS));
        pm->active_plugin(new id_name(PLUGIN_LIFECYCLE));
        
        send_to(new id_name(PLUGIN_LIFECYCLE), EVT_START_FRAMEWORK, conf_path);
    }
    
    void loader::unload() {
        send_to(new id_name(PLUGIN_LIFECYCLE), EVT_STOP_FRAMEWORK);
        
        plugin_manager* pm = plugin_manager::instance();
        while (pm->get_all_plugin().size() > 2) {
            sleep(1);
        }
        
        pm->rm_plugin(new id_name(PLUGIN_LIFECYCLE));
        g_lifecycle = nullptr;
        
        pm->rm_plugin(new id_name(PLUGIN_BUS));
        g_bus = nullptr;
        
        do_cleanup();
    }

}

