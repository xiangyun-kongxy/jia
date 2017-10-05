/**
 * copyright @2016. all rights reserved.
 *
 * @since:  11:10 8/19/16
 * @author: xiangyun kong
 *
 * description:
 *
 */

#include "thread.h"
#include <pthread/pthread.h>
#include <unistd.h>

namespace kxy {
    
    thread::thread() {
        change_status(pending);
        pthread_mutex_init(&m_mutex, nullptr);
    }
    
    thread::~thread() {
        pthread_mutex_destroy(&m_mutex);
    }
    
    void* thread::thread_func(void *param) {
        thread *obj = (thread*)param;
        while (obj->get_status() != destroyed) {
            obj->update_status();
            if (obj->get_status() == running) {
                obj->run_once();
            } else {
                usleep(16);
            }
        }
        return nullptr;
    }
    
    string thread::type() const {
        return "thread";
    }
    
    bool thread::is_kind_of(const string &type_name) const {
        return type_name == "thread" || object::is_kind_of(type_name);
    }
    
    long thread::start() {
        change_status(resuming);
        return pthread_create(&m_thread, nullptr, thread::thread_func, this);
    }
    
    long thread::pause() {
        change_status(pausing);
        return 0;
    }
    
    long thread::resume() {
        change_status(resuming);
        return 0;
    }
    
    long thread::stop(bool force) {
        int result = 0;
        if (force) {
            result = pthread_cancel(m_thread);
            m_thread = nullptr;
            change_status(pending);
        } else {
            change_status(destroying);
        }
        return result;
    }

    void thread::update_status() {
        long status = pausing;
        m_status.compare_exchange_strong(status, paused);

        status = resuming;
        m_status.compare_exchange_strong(status, running);

        status = destroying;
        if (m_status.compare_exchange_strong(status, destroyed)) {
            pthread_cancel(m_thread);
            change_status(pending);
        }
    }

    void thread::change_status(kxy::thread::status s) {
        m_status = s;
    }

    thread::status thread::get_status() {
        return (status)(long)m_status;
    }
    
    pthread_t thread::thread_id() const {
        return m_thread;
    }
    
}
