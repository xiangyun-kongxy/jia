//
//  thread_manager.cpp
//  plugin
//
//  Created by xiangyun.kong on 10/27/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "thread_manager.hpp"

#include <lib/init/initializer.hpp>

#include <plugin/thread/plugin_thread.hpp>
#include <plugin/thread/help_thread.hpp>

namespace pf {

    extern recursive_mutex g_plugin_managing_mutex;
#define DEFAULT_HELP_THREAD_COUNT       4

    thread_manager* g_thread_manager = nullptr;

    void __uninit_thread_manager() {
        delete g_thread_manager;
        g_thread_manager = nullptr;
    }

    void __attribute__((constructor)) __init_thread_manager() {
        g_thread_manager = new thread_manager;

        register_uninitializer("uninitialize thread manager",
                               __uninit_thread_manager);
    }

    thread_manager::thread_manager() {
        pthread_key_create(&m_thread_context_key, __destroy_thread_context);

        for (long i = 0; i < DEFAULT_HELP_THREAD_COUNT; ++i) {
            ptr<help_thread> thread = new help_thread(&m_thread_context_key);
            m_threads[thread->thread_id()] = thread;

            thread->resume();
        }
    }

    thread_manager::~thread_manager() {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);
        
        m_threads.clear();
    }

    thread_manager* thread_manager::instance() {
        return g_thread_manager;
    }

    void thread_manager::__destroy_thread_context(void *param) {
        delete (thread_context_info*) param;
    }

    pthread_t
    thread_manager::create_thread_for_plugin(ptr<pf::plugin> owner) {
        ptr<plugin_thread> thread;
        thread = new plugin_thread(owner->tasks(), owner,
                                   &m_thread_context_key);

        pthread_t thread_id = thread->thread_id();
        
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);
        m_threads[thread_id] = thread;
        return thread_id;
    }

    void thread_manager::delete_thread(pthread_t thread) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);
        m_threads.erase(thread);
    }

    void thread_manager::suspend_thread(pthread_t t) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        ptr<thread> th = m_threads[t];
        if (th != nullptr) {
            th->pause();
        }
    }

    void thread_manager::resume_thread(pthread_t t) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);
        
        ptr<thread> th = m_threads[t];
        if (th != nullptr) {
            th->resume();
        }
    }

    void thread_manager::enable_help_thread(ptr<pf::plugin> pl) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        map<pthread_t, ptr<thread>>::iterator i;
        for (i = m_threads.begin(); i != m_threads.end(); ++i) {
            if (i->second->is_kind_of(OBJ_HELP_THREAD)) {
                ptr<help_thread> thread = i->second;
                thread->add_helping(pl, pl->tasks());
            }
        }
    }

    void thread_manager::disable_help_thread(ptr<pf::plugin> pl) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        map<pthread_t, ptr<thread>>::iterator i;
        for (i = m_threads.begin(); i != m_threads.end(); ++i) {
            if (i->second->is_kind_of(OBJ_HELP_THREAD)) {
                ptr<help_thread> thread = i->second;
                thread->rm_helping(pl);
            }
        }
    }

    ptr<plugin> thread_manager::current_plugin() {
        thread_context_info* ci;
        ci = (thread_context_info*) pthread_getspecific(m_thread_context_key);

        if (ci != nullptr) {
            return ci->plugin;
        } else {
            return nullptr;
        }
    }

    ptr<event> thread_manager::current_task() {
        thread_context_info* ci;
        ci = (thread_context_info*) pthread_getspecific(m_thread_context_key);

        if (ci != nullptr) {
            return ci->task;
        } else {
            return nullptr;
        }
    }
    
}
