//
//  log_service.cpp
//  common
//
//  Created by 孔祥云 on 10/21/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#include <stdio.h>

#include <lib/init/initializer.hpp>

#include <log.hpp>

#include <map>

using namespace std;

namespace kxy {
    
#define CUR_LOG_LEVEL       LL_INFO
    
    map<string, ptr<logger>>* g_log_stores = nullptr;
    
    void __uninit_log_stores() {
        g_log_stores->clear();
    }
    
    void __attribute__((constructor)) __init_log_stores() {
        g_log_stores = new map<string, ptr<logger>>;
        
        logs::set_logger("debug", "/mind/log/debug.log", CUR_LOG_LEVEL);
        logs::set_logger("info", "/mind/log/info.log", CUR_LOG_LEVEL);
        logs::set_logger("warn", "/mind/log/warn.log", CUR_LOG_LEVEL);
        logs::set_logger("error", "/mind/log/error.log", CUR_LOG_LEVEL);
        
        logs::set_logger("bus", "/mind/log/bus.log", CUR_LOG_LEVEL);
        
        register_uninitializer("uninitialize logstores", __uninit_log_stores);
    }
    
    ptr<logger> logs::get_logger(const string &name) {
        return (*g_log_stores)[name];
    }
    
    void logs::set_logger(const string &name, const string &file, kxy::log_level level) {
        FILE* fd = fopen(file.c_str(), "a");
        (*g_log_stores)[name] = new logger(fd, level);
    }
}
