//
//  ipc.hpp
//  bus
//
//  Created by xiangyun.kong on 10/3/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef ipc_h
#define ipc_h

#include <lib/serialize/serializable.hpp>
#include <lib/identifier/identifier.hpp>

#include <plugin/plugin/plugin.hpp>
#include <plugin/event/simple_event.hpp>

using namespace kxy;

namespace pf {

    typedef void (*fcallback)(ptr<object>);

    ptr<object> wait_object(ptr<identifier>);
    void send_message(ptr<event>);
    ptr<response> call_function(ptr<event>);
    void call_function(ptr<event>, fcallback);



    template<typename value_type>
    ptr<serializable> pack_data(ptr<serializable> ar, value_type value) {
        ar << value;
        return ar;
    }
    
    template<typename value_type, typename ...other_types>
    ptr<serializable> pack_data(ptr<serializable>& ar, value_type value,
                                other_types... other) {
        ar << value;
        pack_data(ar, other...);
        return ar;
    }
    
    ptr<serializable> pack_data(ptr<serializable>&);

    template<typename ...ptype>
    ptr<serializable> call(const string& func_name, ptype... params) {
        ptr<serializable> param = new serializable;
        param = pack_data(params...);
        ptr<event> evt = new simple_event(func_name, param);
        ptr<response> rsp = call_function(evt);

        if (rsp != nullptr) {
            ptr<serializable> data = rsp->context();
            return data;
        }
        return nullptr;
    }

    template<typename ...ptype>
    ptr<serializable> call_plugin(ptr<identifier> plugin, const string& func_name,
                                  ptype... params) {
        ptr<serializable> param = new serializable;
        pack_data(param, params...);
        ptr<event> evt = new simple_event(func_name, param, plugin);
        ptr<response> rsp = call_function(evt);
        if (rsp != nullptr) {
            ptr<serializable> data = rsp->context();
            return data;
        }
        return nullptr;
    }
    
    template<typename ...ptype>
    void send_to(ptr<identifier> plugin, const string& event, ptype... params) {
        ptr<class event> evt;
        ptr<serializable> param = new serializable;
        pack_data(param, params...);
        evt = new simple_event(event, param, plugin);
        send_message(evt);
    }
    
    template<typename ...ptype>
    void broadcast(const string& event, ptype... params) {
        ptr<class event> evt;
        ptr<serializable> param = new serializable;
        pack_data(param, params...);
        evt = new simple_event(event, param);
        send_message(evt);
    }
}

#endif /* ipc_h */
