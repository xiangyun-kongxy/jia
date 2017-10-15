/*
 *  ipc.cpp
 *  ipc
 *
 *  Created by 孔祥云 on 10/14/17.
 *  Copyright © 2017 孔祥云. All rights reserved.
 *
 */


#include <bus/bus.h>
#include <sys/fcntl.h>
#include <executor/executor.h>
#include <identifier/id_name.h>
#include <plugin/plugin.h>
#include <event/simple_event.h>

#include <functions.h>
#include <ipc.hpp>

namespace pf {
    
    extern ptr<plugin> g_bus;
    
    void send_message(ptr<event> evt) {
        if(g_bus != nullptr) {
            ptr<serializable> data = new serializable;
            data << evt;
            ptr<event> route_event = new simple_event(F_ROUTE, data);
            
            g_bus->on_event(route_event);
        }
    }
    
    ptr<response> do_task(ptr<task> tsk) {
        ptr<response> rsp = nullptr;
        ptr<bus> pbus = g_bus;
        
        if(pbus != nullptr) {
            ptr<serializable> data = new serializable;
            data << tsk;
            ptr<event> route_event = new simple_event(F_ROUTE, data);
            
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
            ptr<event> route_event = new simple_event(F_ROUTE, data);
            
            pbus->add_pending_task(tsk, callback);
            pbus->on_event(route_event);
        }
    }
    
    ptr<serializable> pack_data() {
        return new serializable;
    }
}
