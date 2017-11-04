/*
 *  loader.cpp
 *  loader
 *
 *  Created by 孔祥云 on 12/31/16.
 *  Copyright © 2016 孔祥云. All rights reserved.
 *
 */

#include "loader.hpp"

#include <lib/identifier/id_name.hpp>
#include <lib/init/initializer.hpp>

#include <plugin/plugin/plugin.hpp>
#include <plugin/manager/plugin_manager.hpp>
#include <plugin/manager/dependence_manager.hpp>

#include <ps/ps.hpp>

#include <bus/bus.hpp>

#include <lifecycle/lifecycle.hpp>

#include <messages.hpp>
#include <class_names.hpp>

#include <log.hpp>

#include <sys/signal.h>
#include <unistd.h>

using namespace kxy;
namespace pf {

    class terminal : public plugin {
    public:
        DECLARE_TYPE(plugin, "terminal");
        IMPL_BEGIN
        IMPL_END
    };

    
    extern ptr<plugin> g_lifecycle;
    extern ptr<plugin> g_bus;
    extern ptr<plugin> g_terminal;
    extern ptr<plugin> g_ps;

    void sig_func(int);
    
    void loader::load(const string& conf_path) {
        g_terminal = new terminal;

        info_log("info","publish-subscribe is loading...");
        g_ps = new ps();
        g_ps->init();
        g_ps->resume();
        info_log("info", "publish-subscribe is loaded");

        info_log("info","bus is loading...");
        g_bus = new bus();
        g_bus->init();
        g_bus->resume();
        info_log("info", "bus is loaded");

        info_log("info", "lifecycle is loading...");
        g_lifecycle = new lifecycle();
        g_lifecycle->init();
        g_lifecycle->resume();
        info_log("info", "lifecycle is loaded");

        send_to(new id_name(PLUGIN_LIFECYCLE), M_START_FRAMEWORK, conf_path);

        signal(SIGABRT, sig_func);
        signal(SIGTERM, sig_func);
        signal(SIGQUIT, sig_func);
        signal(SIGINT,  sig_func);

        signal(SIGHUP, SIG_IGN);
        
    }
    
    void loader::unload() {
        send_to(new id_name(PLUGIN_LIFECYCLE), M_STOP_FRAMEWORK);

        plugin_manager* pm = plugin_manager::instance();
    
        while (pm->get_all_plugin().size() > 3 ||
               pm->has_task(new id_name(PLUGIN_LIFECYCLE)) ||
               pm->has_task(new id_name(PLUGIN_BUS)) ||
               pm->has_task(new id_name(PLUGIN_PS))) {
            sleep(1);
        }

        info_log("info", "lifecycle is exiting...");
        g_lifecycle->uninit();
        g_lifecycle = nullptr;
        info_log("info", "lifecycle is exited");

        info_log("info", "bus is exiting...");
        g_bus->uninit();
        g_bus = nullptr;
        info_log("info", "bus is exited");

        info_log("info", "publish-subscribe is exiting...");
        g_ps->uninit();
        g_ps = nullptr;
        info_log("info", "publish-subscribe is exited");
        
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
                do_cleanup();
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

