//
//  start.hpp
//  console
//
//  Created by 孔祥云 on 11/4/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef start_h
#define start_h

#include <console/terminal.hpp>

#include <lib/init/initializer.hpp>

#include <ps/ps.hpp>
#include <bus/bus.hpp>
#include <lifecycle/lifecycle.hpp>

#include <log.hpp>
#include <ipc.hpp>
#include <messages.hpp>

#include <sys/signal.h>
#include <unistd.h>

namespace pf {
    
    class start : public executor {
    public:
        DECLARE_TYPE(executor, "exe_start");
        
    public:
        static void sig_func(int sig) {
            switch (sig) {
                case SIGABRT:
                case SIGTERM:
                case SIGQUIT:
                case SIGINT:
                    signal(SIGABRT, SIG_IGN);
                    signal(SIGTERM, SIG_IGN);
                    signal(SIGQUIT, SIG_IGN);
                    signal(SIGINT,  SIG_IGN);
                    send_to(new id_name(PLUGIN_TERMINAL), "stop");
                    break;
                case SIGTSTP:
                default:
                    break;
            }
        }
        
        ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            extern ptr<plugin> g_lifecycle;
            extern ptr<plugin> g_bus;
            extern ptr<plugin> g_ps;
            
            string path;
            evt->param() >> path;
            
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
            
            send_to(new id_name(PLUGIN_LIFECYCLE), M_START_FRAMEWORK, path);
            
            signal(SIGABRT, sig_func);
            signal(SIGTERM, sig_func);
            signal(SIGQUIT, sig_func);
            signal(SIGINT,  sig_func);
            signal(SIGHUP,  SIG_IGN);
            
            ptr<terminal> term = owner;
            (**term)["framework"] = "loaded";
            
            return nullptr;
        }
    };
                
}
                
#endif /* start_h */
