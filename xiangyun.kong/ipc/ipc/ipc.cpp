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

#include <ps/ps.hpp>

#include <plugin/event/simple_event.hpp>
#include <plugin/manager/plugin_manager.hpp>

#include <messages.hpp>
#include <ipc.hpp>

using namespace std;

namespace pf {

    extern ptr<plugin> g_bus;
    extern ptr<plugin> g_ps;

    ptr<object> wait(ptr<identifier> id) {
        long key = ((ptr<ps>)g_ps)->subscribe(id);
        return ((ptr<ps>)g_ps)->wait(key);
    }
    
    void send(ptr<event> evt) {
        g_bus->tasks()->push(evt);
        ((ptr<ps>)g_ps)->tasks()->push(evt);
    }

    ptr<response> call(ptr<event> evt) {
        long key = ((ptr<ps>)g_ps)->subscribe(new id_response(evt));
        g_bus->tasks()->push(evt);
        ((ptr<ps>)g_ps)->tasks()->push(evt);
        return ((ptr<ps>)g_ps)->wait(key);
    }
    
    void call(ptr<event> evt, fcallback callback) {
        ((ptr<ps>)g_ps)->subscribe(new id_response(evt), callback);
        g_bus->tasks()->push(evt);
        ((ptr<ps>)g_ps)->tasks()->push(evt);
    }
    
    ptr<serializable> pack_data(ptr<serializable>& ar) {
        return ar;
    }
}
