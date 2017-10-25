//
//  logger.hpp
//  common
//
//  Created by 孔祥云 on 10/21/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef logger_hpp
#define logger_hpp

#include <stdio.h>

#include <lib/object/object.h>

#include <names.h>

#include <sys/time.h>
#include <mutex>

using namespace std;

namespace kxy {
    
#define MAX_LOG_LINE_SIZE           4096 
#define SYNC_LOG_LATENCY            1
    
    enum log_level {
        LL_DEBUG,
        LL_INFO,
        LL_WARN,
        LL_ERROR,
    };
    
    class logger : public object {
    public:
        DECLARE_TYPE(object, OBJ_LOGGER);
        
    public:
        logger(FILE* fd, log_level level);
        virtual ~logger();
        
    public:
        void debug(const string& msg);
        void info(const string& msg);
        void warn(const string& msg);
        void error(const string& msg);
        
    protected:
        void _log(const timeval& tv, pthread_t thread, log_level level, const string& msg);
        static void* _commit_log(void*);
        
    private:
        FILE* m_fd;
        long m_level;
        
        string m_buf;

        mutex m_mutex;
        pthread_t m_thread;
    };
}

#endif /* logger_hpp */
