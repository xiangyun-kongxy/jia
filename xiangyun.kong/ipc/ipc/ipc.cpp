/*
 *  ipc.cpp
 *  ipc
 *
 *  Created by 孔祥云 on 10/14/17.
 *  Copyright © 2017 孔祥云. All rights reserved.
 *
 */


#include <sys/fcntl.h>
#include <sys/time.h>
#include <set>

#include <lib/identifier/id_name.h>
#include <lib/container/cqueue.h>

#include <bus/bus.h>

#include <plugin/executor/executor.h>
#include <plugin/event/simple_event.h>
#include <plugin/manager/plugin_manager.hpp>

#include <common/identifier/id_task_response.hpp>

#include <events.h>
#include <ipc.hpp>

using namespace std;

namespace pf {

    // static const timeval MAX_TIMEOUT = {120, 0};
    static const timeval TIMEOUT = {10, 0};
    
    extern ptr<plugin> g_bus;
    set<ptr<task>> g_waiting_tasks;
    ptr<cqueue<ptr<object>>> g_bus_pool = nullptr;

    ptr<cqueue<ptr<object>>> get_bus_pool() {
        if (g_bus_pool == nullptr) {
            plugin_manager *pm = plugin_manager::instance();
            const plugin_info* pi = pm->find_plugin(new id_name(PLUGIN_BUS));
            g_bus_pool = pi->threads->front()->pool();
        }
        return g_bus_pool;
    }
    
    ptr<object> wait_event(ptr<identifier> id) {
        if (g_bus != nullptr) {
            timeval timeout;
            gettimeofday(&timeout, nullptr);
            timeout.tv_sec += TIMEOUT.tv_sec;
            timeout.tv_usec += TIMEOUT.tv_usec;
            ((ptr<bus>)g_bus)->set_waiting(id);
            return ((ptr<bus>)g_bus)->wait_object(id, timeout);
        }
        return nullptr;
    }
    
    void send_message(ptr<event> evt) {
        if (g_bus != nullptr) {

            ptr<serializable> data = new serializable;
            data << evt;
            ptr<event> route_event = new simple_event(EVT_ROUTE, data);
            
            get_bus_pool()->push(route_event);
        }
    }

    ptr<response> do_task(ptr<task> tsk) {
        if (g_bus != nullptr) {
            ptr<serializable> data = new serializable;
            data << tsk;
            ptr<event> route_event = new simple_event(EVT_ROUTE, data);

            ptr<id_task_response> id = new id_task_response(tsk);
            ((ptr<bus>)g_bus)->set_waiting(id);
            get_bus_pool()->push(route_event);

            timeval timeout;
            gettimeofday(&timeout, nullptr);
            timeout.tv_sec += TIMEOUT.tv_sec;
            timeout.tv_usec += TIMEOUT.tv_usec;
            return ((ptr<bus>)g_bus)->wait_object(id, timeout);
        }
        
        return nullptr;
    }
    
    void do_task_async(ptr<task> tsk, task_callback callback) {
        if (g_bus != nullptr) {
            ptr<serializable> data = new serializable;
            data << tsk;
            ptr<event> route_event = new simple_event(EVT_ROUTE, data);
            
            ((ptr<bus>)g_bus)->set_event_trigger(new id_task_response(tsk),
                                                 callback);
            get_bus_pool()->push(route_event);
        }
    }
    
    ptr<serializable> pack_data() {
        return new serializable;
    }
}
