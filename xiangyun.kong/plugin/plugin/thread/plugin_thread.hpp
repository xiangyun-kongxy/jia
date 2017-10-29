//
//  plugin_thread.hpp
//  plugin
//
//  Created by xiangyun.kong on 10/27/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef plugin_thread_h
#define plugin_thread_h


#include <unistd.h>

#include <lib/thread/thread.hpp>
#include <lib/container/cqueue.hpp>

#include <plugin/response/response.hpp>
#include <plugin/event/event.hpp>
#include <plugin/event/simple_event.hpp>
#include <plugin/plugin/plugin.hpp>

#include <messages.hpp>

using namespace std;
using namespace kxy;

namespace pf {

    struct thread_context_info {
        ptr<plugin> plugin;
        ptr<event> task;
    };


    class plugin_thread : public thread {
    public:
        DECLARE_TYPE(thread, OBJ_PLUGIN_THREAD);

    public:
        plugin_thread(ptr<cqueue<ptr<object>>> pool, ptr<plugin> owner,
                      pthread_key_t* thread_context_key) {
            m_owner = owner;
            m_pool = pool;
            m_cur_task = nullptr;
            m_thread_context = thread_context_key;
        }

        virtual ~plugin_thread() {
            change_status(stopping);
            
            // waking thread up
            for (long i = 0; i < 1024; ++i)
                m_pool->push(nullptr);
            
            wait_status();
        }

    public:
        virtual void* run_once() override {
            m_cur_task = m_pool->pop();

            thread_context_info* ci;
            ci = (thread_context_info*) pthread_getspecific(*m_thread_context);
            if (ci == nullptr) {
                ci = new thread_context_info;
                ci->plugin = m_owner;
                ci->task = nullptr;
                pthread_setspecific(*m_thread_context, ci);
            }
            ci->task = m_cur_task;

            if(m_cur_task == nullptr) {
                usleep(12);
            } else {
                ptr<response> rsp = m_owner->do_task(m_cur_task);
                if (rsp != nullptr) {
                    extern ptr<plugin> g_ps;
                    g_ps->tasks()->push(rsp);
                }
            }
            return 0;
        }

        virtual void wait_status() override {
            m_pool->push(nullptr);
            thread::wait_status();
        }

        ptr<cqueue<ptr<object>>> pool() const {
            return m_pool;
        }

        ptr<plugin> owner() const {
            return m_owner;
        }

        ptr<object> cur_task() const {
            return m_cur_task;
        }

    protected:
        ptr<cqueue<ptr<object>>> m_pool;
        ptr<plugin> m_owner;
        ptr<event> m_cur_task;
        pthread_key_t* m_thread_context;
    };

}

#endif /* plugin_thread_h */
