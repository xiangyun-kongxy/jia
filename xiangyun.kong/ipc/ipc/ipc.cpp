/*
 *  ipc.cpp
 *  ipc
 *
 *  Created by 孔祥云 on 10/14/17.
 *  Copyright © 2017 孔祥云. All rights reserved.
 *
 */


#include <sys/time.h>

#include <lib/identifier/id_name.hpp>
#include <lib/container/cqueue.hpp>

#include <bus/bus.hpp>

#include <plugin/event/simple_event.hpp>
#include <plugin/manager/plugin_manager.hpp>

#include <messages.hpp>
#include <ipc.hpp>

using namespace std;

namespace pf {

    static const timeval TIMEOUT = {10, 0};
    
    extern ptr<plugin> g_bus;
    
    ptr<object> wait_object(ptr<identifier> id) {
        ((ptr<bus>)g_bus)->add_waiting_object(id);
        
        timeval timeout;
        gettimeofday(&timeout, nullptr);
        timeout.tv_sec += TIMEOUT.tv_sec;
        timeout.tv_usec += TIMEOUT.tv_usec;
        return ((ptr<bus>)g_bus)->wait_object(id, timeout);
    }
    
    void send_message(ptr<event> evt) {
        evt->should_response() = false;
        g_bus->tasks()->push(evt);
    }

    ptr<response> call_function(ptr<event> evt) {
        evt->should_response() = true;
        ((ptr<bus>)g_bus)->add_rsp_trigger(evt, nullptr);
        g_bus->tasks()->push(evt);

        timeval timeout;
        gettimeofday(&timeout, nullptr);
        timeout.tv_sec += TIMEOUT.tv_sec;
        timeout.tv_usec += TIMEOUT.tv_usec;
        return ((ptr<bus>)g_bus)->wait_response(evt, timeout);
    }
    
    void call_function(ptr<event> evt, fcallback callback) {
        evt->should_response() = true;
        ((ptr<bus>)g_bus)->add_rsp_trigger(evt, callback);
        g_bus->tasks()->push(evt);
    }
    
    ptr<serializable> pack_data(ptr<serializable>& ar) {
        return ar;
    }
}
