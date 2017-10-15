//
//  ipc.hpp
//  bus
//
//  Created by xiangyun.kong on 10/3/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef ipc_h
#define ipc_h

#include <serialize/serializable.hpp>
#include <response/response.h>
#include <task/simple_task.h>
#include <event/simple_event.h>
#include <identifier/identifier.h>

using namespace kxy;

namespace pf {

    class plugin;
    typedef void (*callback)(ptr<task>, ptr<response>);
    extern ptr<serializable> pack_data();

    extern void send_message(ptr<event>);
    extern ptr<response> do_task(ptr<task>);
    extern void do_task_async(ptr<task>, callback);


    template<typename value_type, typename ...other_types>
    ptr<serializable> pack_data(value_type value, other_types... other) {
        ptr<serializable> result = pack_data(other...);
        result << value;
        return result;
    }

    template<typename value_type>
    ptr<serializable> pack_data(value_type value) {
        ptr<serializable> ar = new serializable;
        ar << value;
        return ar;
    }

    template<typename ...ptype>
    ptr<serializable> call(const string& func_name, ptype... params) {
        ptr<serializable> param = pack_data(params...);
        ptr<task> task = new simple_task(func_name, param);
        ptr<response> rsp = do_task(task);
        ptr<serializable> data = rsp->context();
        return data;
    }

    template<typename ...ptype>
    ptr<serializable> call_plugin(ptr<identifier> plugin, const string& func_name,
                                  ptype... params) {
        ptr<serializable> param = pack_data(params...);
        ptr<task> task = new simple_task(func_name, param, plugin);
        ptr<response> rsp = do_task(task);
        ptr<serializable> data = rsp->context();
        return data;
    }
    
    template<typename ...ptype>
    void send_to(ptr<identifier> plugin, const string& event, ptype... params) {
        ptr<class event> evt;
        ptr<serializable> param = pack_data(params...);
        evt = new simple_event(event, param, plugin);
        send_message(evt);
    }
    
    template<typename ...ptype>
    void broadcast(const string& event, ptype... params) {
        ptr<class event> evt;
        ptr<serializable> param = pack_data(params...);
        evt = new simple_event(event, param);
        send_message(evt);
    }
}

#endif /* ipc_h */
