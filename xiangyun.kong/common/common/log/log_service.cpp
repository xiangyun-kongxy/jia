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
        
        FILE* pf;
#ifdef DEBUG
        logs::set_logger("debug", stdout, CUR_LOG_LEVEL);
        logs::set_logger("info", stdout, CUR_LOG_LEVEL);
        logs::set_logger("warn", stdout, CUR_LOG_LEVEL);
        logs::set_logger("error", stdout, CUR_LOG_LEVEL);
#else
        pf = fopen("/mind/log/debug.log", "a");
        logs::set_logger("debug", pf, CUR_LOG_LEVEL);
        
        pf = fopen("/mind/log/info.log", "a");
        logs::set_logger("info", pf, CUR_LOG_LEVEL);
        
        pf = fopen("/mind/log/warn.log", "a");
        logs::set_logger("warn", pf, CUR_LOG_LEVEL);
        
        pf = fopen("/mind/log/error.log", "a");
        logs::set_logger("error", pf, CUR_LOG_LEVEL);
#endif
        pf = fopen("/mind/log/bus.log", "a");
        logs::set_logger("bus", pf, CUR_LOG_LEVEL);
        
        register_uninitializer("uninitialize logstores", __uninit_log_stores);
    }
    
    ptr<logger> logs::get_logger(const string &name) {
        return (*g_log_stores)[name];
    }
    
    void logs::set_logger(const string &name, FILE* file, kxy::log_level level) {
        (*g_log_stores)[name] = new logger(file, level);
    }
    
    
    const char* filename(const char* path) {
        const char* pc;
        while ((pc = strchr(path, '/')) != nullptr) {
            path = pc + 1;
        }
        return path;
    }
    
}
