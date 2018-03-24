//
//  config_center.cpp
//  config_center
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "config_center.hpp"

#include <lib/fs/kv.hpp>

#include <config_center/executor/exe_get_config.hpp>
#include <config_center/executor/exe_put_config.hpp>

namespace kxy {
    
    const string config_center::m_service = "config_service/";
    
    config_center::config_center() {
        m_executors[M_GET_CONFIG] = new get_config;
        m_executors[M_PUT_CONFIG] = new put_config;
    }
    
    string config_center::get(const string& ns, const string &key) {
        return kv_get(m_service + ns, key);
    }
    
    void config_center::put(const string& np,
                            const string &key, const string &value) {
        kv_put(m_service + ns, key, value);
    }
    
    extern "C" void* init_config_center(void* conf) {
        config_center* plugin = new config_center;
        return plugin;
    }
}
