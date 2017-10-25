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
#include <plugin/manager/plugin_manager.hpp>
#include <plugin/manager/dependence_manager.hpp>

#include <bus/bus.h>

#include <lifecycle/lifecycle.hpp>

#include <events.h>
#include <names.h>

#include <log.hpp>

#include <sys/signal.h>

using namespace kxy;
namespace pf {
    
    extern ptr<plugin> g_lifecycle;
    extern ptr<plugin> g_bus;

    void sig_func(int);
    
    void loader::load(const string& conf_path) {
        plugin_manager* pm = plugin_manager::instance();

        info_log(logs::get_logger("info"),"bus is loading...");
        g_bus = new bus();
        pm->add_plugin(g_bus);
        pm->active_plugin(new id_name(PLUGIN_BUS));
        info_log(logs::get_logger("info"), "bus is loaded");

        info_log(logs::get_logger("info"), "lifecycle is loading...");
        g_lifecycle = new lifecycle();
        pm->add_plugin(g_lifecycle);
        pm->active_plugin(new id_name(PLUGIN_LIFECYCLE));
        info_log(logs::get_logger("info"), "lifecycle is loaded");

        send_to(new id_name(PLUGIN_LIFECYCLE), EVT_START_FRAMEWORK, conf_path);

        signal(SIGABRT, sig_func);
        signal(SIGTERM, sig_func);
        signal(SIGQUIT, sig_func);
        signal(SIGINT,  sig_func);

        signal(SIGHUP, nullptr);
        
    }
    
    void loader::unload() {
        send_to(new id_name(PLUGIN_LIFECYCLE), EVT_STOP_FRAMEWORK);

        plugin_manager* pm = plugin_manager::instance();
    
        while (pm->get_all_plugin().size() > 2 ||
               pm->have_task(new id_name(PLUGIN_LIFECYCLE)) ||
               pm->have_task(new id_name(PLUGIN_BUS))) {
            sleep(1);
        }

        info_log(logs::get_logger("info"), "lifecycle is exiting...");
        pm->rm_plugin(new id_name(PLUGIN_LIFECYCLE));
        g_lifecycle = nullptr;
        info_log(logs::get_logger("info"), "lifecycle is exited");

        info_log(logs::get_logger("info"), "bus is exiting...");
        pm->rm_plugin(new id_name(PLUGIN_BUS));
        g_bus = nullptr;
        info_log(logs::get_logger("info"), "bus is exited");

        do_cleanup();
    }

    void sig_func(int sig) {
        switch (sig) {
            case SIGABRT:
            case SIGTERM:
            case SIGQUIT:
            case SIGINT:
                signal(SIGABRT, SIG_IGN);
                signal(SIGTERM, SIG_IGN);
                signal(SIGQUIT, SIG_IGN);
                signal(SIGINT,  SIG_IGN);
                loader::unload();
                signal(SIGABRT, SIG_DFL);
                signal(SIGTERM, SIG_DFL);
                signal(SIGQUIT, SIG_DFL);
                signal(SIGINT,  SIG_DFL);
                exit(0);
                break;
            case SIGTSTP:
            default:
                break;
        }
    }

}

