/*
 *  ipc.cpp
 *  ipc
 *
 *  Created by 孔祥云 on 10/14/17.
 *  Copyright © 2017 孔祥云. All rights reserved.
 *
 */


#include <sys/fcntl.h>
#include <set>

#include <lib/identifier/id_name.h>

#include <bus/bus.h>

#include <plugin/executor/executor.h>
#include <plugin/event/simple_event.h>

#include <common/identifier/id_task_response.hpp>

#include <events.h>
#include <ipc.hpp>

using namespace std;

namespace pf {
    
    extern ptr<bus> g_bus;
    set<ptr<task>> g_waiting_tasks;

    ptr<object> wait_event(ptr<identifier> id) {
        if (g_bus != nullptr) {
            return g_bus->wait_object(id);
        }
        return nullptr;
    }
    
    void send_message(ptr<event> evt) {
        if (g_bus != nullptr) {
            ptr<serializable> data = new serializable;
            data << evt;
            ptr<event> route_event = new simple_event(EVT_ROUTE, data);
            
            g_bus->on_event(route_event);
        }
    }
    
    ptr<response> do_task(ptr<task> tsk) {
        if (g_bus != nullptr) {
            ptr<serializable> data = new serializable;
            data << tsk;
            ptr<event> route_event = new simple_event(EVT_ROUTE, data);

            ptr<id_task_response> id = new id_task_response(tsk);
            g_bus->hold_object(id);
            g_bus->on_event(route_event);
            return g_bus->wait_object(id);
        }
        
        return nullptr;
    }
    
    void do_task_async(ptr<task> tsk, task_callback callback) {
        if (g_bus != nullptr) {
            ptr<serializable> data = new serializable;
            data << tsk;
            ptr<event> route_event = new simple_event(EVT_ROUTE, data);
            
            g_bus->set_event_trigger(new id_task_response(tsk), callback);
            g_bus->on_event(route_event);
        }
    }
    
    ptr<serializable> pack_data() {
        return new serializable;
    }
}
