//
//  stop.hpp
//  console
//
//  Created by 孔祥云 on 11/4/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef stop_h
#define stop_h

#include <console/terminal.hpp>

#include <lib/init/initializer.hpp>

#include <log.hpp>
#include <ipc.hpp>
#include <messages.hpp>

#include <sys/signal.h>

namespace pf {
    
    class stop : public executor {
    public:
        DECLARE_TYPE(executor, "exe_stop");
        
    public:
        ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            extern ptr<plugin> g_lifecycle;
            extern ptr<plugin> g_bus;
            extern ptr<plugin> g_ps;
            
            ptr<terminal> term = owner;
            
            send_to(new id_name(PLUGIN_LIFECYCLE), M_STOP_FRAMEWORK);
            
            plugin_manager* pm = plugin_manager::instance();
            
            while (pm->get_all_plugin().size() > 4 ||
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
            
            signal(SIGABRT, SIG_IGN);
            signal(SIGTERM, SIG_IGN);
            signal(SIGQUIT, SIG_IGN);
            signal(SIGINT,  SIG_IGN);
            signal(SIGHUP,  SIG_IGN);
            
            (**term)["framework"] = "unloaded";
            
            return nullptr;
        }
    };
    
}

#endif /* stop_h */
