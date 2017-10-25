//
//  logger.cpp
//  common
//
//  Created by 孔祥云 on 10/21/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#include "logger.hpp"

#include <plugin/manager/plugin_manager.hpp>

#include <log.hpp>

using namespace pf;

namespace kxy {
    
    logger::logger(FILE* fd, log_level level) {
        m_fd = fd;
        m_level = level;
        pthread_create(&m_thread, nullptr, logger::_commit_log, this);
    }
    
    logger::~logger() {
        pthread_cancel(m_thread);
        _commit_log(this);
        fclose(m_fd);
    }
    
    void logger::debug(const string& msg) {
        if (logs::get_logger("debug") != this) {
            logs::get_logger("debug")->debug(msg);
        }

        if (m_level >= LL_DEBUG) {
            pthread_t thread;
            timeval now;
            thread = pthread_self();
            gettimeofday(&now, nullptr);
            
            _log(now, thread, LL_DEBUG, msg);
        }
    }
    
    void logger::info(const string& msg) {
        if (logs::get_logger("info") != this) {
            logs::get_logger("info")->info(msg);
        }

        if (m_level >= LL_INFO) {
            pthread_t thread;
            timeval now;
            thread = pthread_self();
            gettimeofday(&now, nullptr);
            
            _log(now, thread, LL_INFO, msg);
        }
    }
    
    void logger::warn(const string& msg) {
        if (logs::get_logger("warn") != this) {
            logs::get_logger("warn")->warn(msg);
        }

        if (m_level >= LL_WARN) {
            pthread_t thread;
            timeval now;
            thread = pthread_self();
            gettimeofday(&now, nullptr);
            
            _log(now, thread, LL_WARN, msg);
        }
    }
    
    void logger::error(const string& msg) {
        if (logs::get_logger("error") != this) {
            logs::get_logger("error")->error(msg);
        }
        
        if (m_level >= LL_ERROR) {
            pthread_t thread;
            timeval now;
            thread = pthread_self();
            gettimeofday(&now, nullptr);
            
            _log(now, thread, LL_ERROR, msg);
        }
    }
    
    void logger::_log(const timeval& tv, pthread_t thread, log_level level,
                      const string& msg) {
        static const char* level_mapping[] = {
            "debug",
            "info",
            "warn",
            "error",
        };

        char tb[32];
        strftime(tb, 32, "%F %T", localtime(&tv.tv_sec));
        
        const char* plugin = "terminal";
        const char* task = "freedom";
        plugin_manager* pm = plugin_manager::instance();
        context_info ci = pm->get_context_by_thread_id(thread);
        if (ci.plugin != nullptr) {
            plugin = ci.plugin->name().c_str();
        }
        if (ci.task != nullptr) {
            task = ci.task->name().c_str();
        }

        char log_buf[MAX_LOG_LINE_SIZE + 1] = "";
        snprintf(log_buf, MAX_LOG_LINE_SIZE,
                 "[%5s][%s %06d][%016lx][%-10s][%-16s]%s\n",
                 level_mapping[level], tb, tv.tv_usec, (long)thread, plugin,
                 task, msg.c_str());
        
        do {
            lock_guard<mutex> _(m_mutex);
            m_buf += log_buf;
        } while (0);
    }
    
    void* logger::_commit_log(void *param) {
        ptr<logger> logger = (class logger*)param;
        
        while (1) {
            do {
                lock_guard<mutex> _(logger->m_mutex);
                
                if (logger->m_buf.length() > 0) {
                    fwrite(logger->m_buf.c_str(), logger->m_buf.length(), 1, logger->m_fd);
                    fflush(logger->m_fd);
                    logger->m_buf = "";
                }
            } while (0);
            sleep(SYNC_LOG_LATENCY);
        }
    }
    
}

