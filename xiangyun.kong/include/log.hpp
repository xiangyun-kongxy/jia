//
//  log.hpp
//  
//
//  Created by 孔祥云 on 10/21/17.
//
//

#ifndef log_h
#define log_h

#include <lib/object/ptr.hpp>

#include <common/log/logger.hpp>

namespace kxy {
    
    class logs {
    public:
        static ptr<logger> get_logger(const string& name);
        static void set_logger(const string& name, FILE* file, log_level level);
    };

#ifdef NO_LOG
    
#define debug_log(logger, msg)
#define info_log(logger, msg)
#define warn_log(logger, msg)
#define error_log(logger, msg)
    
#else
    
    extern const char* filename(const char* path);
#define __extern_message(msg)                                           \
    string __4sxud8_msg__;                                              \
    char buf[128];                                                      \
    snprintf(buf, 128, "[%32s:%-4d]    ",filename(__FILE__),__LINE__);  \
    __4sxud8_msg__ = string(buf) + (msg);
#define debug_log(logger, msg) do { __extern_message(msg);              \
    logs::get_logger(logger)->debug(__4sxud8_msg__); } while(0)
#define info_log(logger, msg)  do { __extern_message(msg);              \
    logs::get_logger(logger)->info(__4sxud8_msg__); } while(0)
#define warn_log(logger, msg)  do { __extern_message(msg);              \
    logs::get_logger(logger)->warn(__4sxud8_msg__); } while(0)
#define error_log(logger, msg) do { __extern_message(msg);              \
    logs::get_logger(logger)->error(__4sxud8_msg__); } while(0)
#endif
    
}

#endif /* log_h */
