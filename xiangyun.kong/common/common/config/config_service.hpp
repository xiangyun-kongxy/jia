//
//  config_service.hpp
//  common
//
//  Created by 孔祥云 on 5/1/18.
//  Copyright © 2018 xiangyun.kong. All rights reserved.
//

#ifndef config_service_hpp
#define config_service_hpp

#include <lib/object/ptr.hpp>
#include <lib/identifier/id_name.hpp>
#include <ipc.hpp>
#include <messages.hpp>

#include <string>

using namespace std;
using namespace kxy;

namespace pf {
    extern ptr<identifier> g_cfg_provider;
    
    template<typename  ty>
    ty read_config(const string& name) {
        ty result = ty();
        
        ptr<serializable> rsp;
        rsp = call_plugin(g_cfg_provider, M_GET_CONFIG, name);
        if (rsp != nullptr) {
            rsp >> result;
        }
        
        return result;
    }
    
    template<typename ty>
    void save_config(const string& name, const ty& value) {
        send_to(g_cfg_provider, M_PUT_CONFIG, name, value);
    }
}

#endif /* config_service_hpp */
