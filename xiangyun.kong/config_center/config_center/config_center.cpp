//
//  config_center.cpp
//  config_center
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "config_center.hpp"
#include "executor/exe_on_get_config.h"
#include "trigger/trigger_on_put_config.h"
#include "config_functions.h"
#include "fs/kv.h"

namespace kxy {
    
    const string config_center::m_service = "config_service";
    
    config_center::config_center() {
        m_task_processor[F_ON_GET_CONFIG] = new exe_on_get_config;
        m_event_processor[F_ON_PUT_CONFIG] = new trigger_on_put_config;
    }
    
    string config_center::get(const string &key) {
        return kv_get(m_service, key);
    }
    
    void config_center::put(const string &key, const string &value) {
        kv_put(m_service, key, value);
    }
    
    string config_center::type() const {
        return "config_center";
    }
    
    bool config_center::is_kind_of(const string &type_name) const {
        return type_name == "config_center" || plugin::is_kind_of(type_name);
    }

    extern "C" void* init_config_center(void* conf) {
        ptr<config_center> plugin = new config_center;
        return *plugin;
    }
}
