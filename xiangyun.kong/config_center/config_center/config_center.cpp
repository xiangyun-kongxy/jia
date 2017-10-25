//
//  config_center.cpp
//  config_center
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "config_center.hpp"

#include <lib/fs/kv.h>

#include <config_center/executor/exe_get_config.h>
#include <config_center/trigger/trigger_put_config.h>

#include <functions.h>
#include <events.h>
#include <names.h>

namespace kxy {
    
    const string config_center::m_service = "config_service";
    
    config_center::config_center() {
        m_executors[F_GET_CONFIG] = new get_config;
        m_triggers[EVT_PUT_CONFIG] = new put_config;
    }
    
    string config_center::get(const string &key) {
        return kv_get(m_service, key);
    }
    
    void config_center::put(const string &key, const string &value) {
        kv_put(m_service, key, value);
    }
    
    extern "C" void* init_config_center(void* conf) {
        config_center* plugin = new config_center;
        return plugin;
    }
}
