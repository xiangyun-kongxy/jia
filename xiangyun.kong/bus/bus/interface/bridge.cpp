//
//  bridge.cpp
//  bus
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include "../bus_functions.h"
#include "../bus.h"
#include "../ipc.hpp"
#include <lock/auto_lock.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <executor/executor.h>
#include <identifier/id_name.h>
#include <plugin/plugin.h>
#include <event/simple_event.h>

namespace pf {
    
    extern ptr<plugin> g_bus;
    
    void send_message(ptr<event> evt) {
        if(g_bus != nullptr) {
            ptr<serializable> data = new serializable;
            data << evt;
            ptr<event> route_event = new simple_event(F_ROUTE_EVENT, data);
            
            g_bus->on_event(route_event);
        }
    }

    ptr<response> do_task(ptr<task> tsk) {
        ptr<response> rsp = nullptr;
        ptr<bus> pbus = g_bus;
        
        if(pbus != nullptr) {
            ptr<serializable> data = new serializable;
            data << tsk;
            ptr<event> route_event = new simple_event(F_ROUTE_EVENT,data);
            
            pbus->add_pending_task(tsk, nullptr);
            pbus->on_event(route_event);
            rsp = pbus->wait_respond(tsk);
        }
        
        return rsp;
    }

    void do_task_async(ptr<task> tsk, callback callback) {
        ptr<bus> pbus = g_bus;
        if(pbus != nullptr) {
            ptr<serializable> data = new serializable;
            data << tsk;
            ptr<event> route_event = new simple_event(F_ROUTE_EVENT, data);
            
            pbus->add_pending_task(tsk, callback);
            pbus->on_event(route_event);
        }
    }

}
