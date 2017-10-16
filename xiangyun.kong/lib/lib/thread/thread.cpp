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

#include <lib/convert/basic_type_convert.h>

namespace kxy {
    
    thread::thread() {
        change_status(pending);
        m_status_changing = sem_open((l2s((long)this) + ".changing").c_str(),
                                     O_CREAT, 0644, 0);
        m_status_changed = sem_open((l2s((long)this) + ".changed").c_str(),
                                    O_CREAT, 0644, 0);
        pthread_mutex_init(&m_mutex, nullptr);
        pthread_create(&m_thread, nullptr, thread::thread_func, this);
    }
    
    thread::~thread() {
        stop();
        pthread_mutex_destroy(&m_mutex);
    }
    
    void* thread::thread_func(void *param) {
        thread *obj = (thread*)param;
        while (obj->status() != destroyed) {
            obj->update_status();
            if (obj->status() == running) {
                obj->run_once();
            } else {
                sem_wait(obj->m_status_changing);
            }
        }
        obj->m_thread = nullptr;
        return nullptr;
    }
    
    string thread::type() const {
        return OBJ_THREAD;
    }
    
    bool thread::is_kind_of(const string &type_name) const {
        return type_name == OBJ_THREAD || object::is_kind_of(type_name);
    }
    
    long thread::start() {
        if (m_thread == nullptr) {
            pthread_create(&m_thread, nullptr, thread::thread_func, this);
        }
        change_status(resuming);
        wait_status();
        return 0;
    }
    
    long thread::pause() {
        change_status(pausing);
        wait_status();
        return 0;
    }
    
    long thread::resume() {
        change_status(resuming);
        wait_status();
        return 0;
    }
    
    long thread::stop(bool force) {
        int result = 0;
        if (m_thread != nullptr) {
            if (force) {
                result = pthread_cancel(m_thread);
                m_thread = nullptr;
                change_status(pending);
            } else {
                change_status(destroying);
                wait_status();
            }
        }
        return result;
    }

    void thread::update_status() {
        long old_status = status();

        long exchange = pausing;
        m_status.compare_exchange_strong(exchange, paused);

        exchange = resuming;
        m_status.compare_exchange_strong(exchange, running);

        exchange = destroying;
        if (m_status.compare_exchange_strong(exchange, destroyed)) {
            pthread_cancel(m_thread);
            m_thread = nullptr;
            change_status(pending);
        }

        if (status() != old_status) {
            sem_post(m_status_changed);
        }
    }

    void thread::change_status(thread_status s) {
        m_status = s;
        if (s == pausing || s == resuming || s == destroying) {
            sem_post(m_status_changing);
        }
    }

    void thread::wait_status() {
        while (true) {
            thread_status s = status();
            if (s == pending || s == paused || s == running || s == destroyed) {
                break;
            }
            sem_wait(m_status_changed);
        }
    }

    thread_status thread::status() {
        return (thread_status)(long)m_status;
    }
    
    pthread_t thread::thread_id() const {
        return m_thread;
    }
    
}
