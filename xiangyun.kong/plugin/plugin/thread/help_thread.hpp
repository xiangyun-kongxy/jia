//
//  help_thread.hpp
//  plugin
//
//  Created by xiangyun.kong on 10/27/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef help_thread_h
#define help_thread_h


#include <unistd.h>

#include <lib/thread/thread.hpp>
#include <lib/container/cqueue.hpp>

#include <plugin/response/response.hpp>
#include <plugin/event/event.hpp>
#include <plugin/event/simple_event.hpp>
#include <plugin/plugin/plugin.hpp>

#include <messages.hpp>

#include <mutex>

using namespace std;
using namespace kxy;

namespace pf {

    class help_thread : public thread {
    public:
        DECLARE_TYPE(thread, OBJ_HELP_THREAD);

    public:
        help_thread(pthread_key_t* thread_context_key) {
            m_thread_context = thread_context_key;
        }

        virtual ~help_thread() {
            kill_thread();
        }

    public:
        virtual void* run_once() override {
            m_cur_task = nullptr;
            do {
                lock_guard<mutex> _(m_mutex);

                m_cur_owner = nullptr;

                container::iterator i;
                for (i = m_helping.begin(); i != m_helping.end(); ++i) {
                    if (i->second->size() > 0) {
                        m_cur_task = i->second->try_pop();
                        if (m_cur_task != nullptr) {
                            m_cur_owner = i->first;
                            break;
                        }
                    }
                }
            } while (0);

            thread_context_info* ci;
            ci = (thread_context_info*) pthread_getspecific(*m_thread_context);
            if (ci == nullptr) {
                ci = new thread_context_info;
                ci->plugin = nullptr;
                ci->task = nullptr;
                pthread_setspecific(*m_thread_context, ci);
            }
            ci->plugin = m_cur_owner;
            ci->task = m_cur_task;

            if (m_cur_task != nullptr) {
                if (m_cur_task->should_response()) {
                    ptr<response> rsp = current_owner()->do_task(m_cur_task);

                    extern ptr<plugin> g_bus;
                    g_bus->on_event((ptr<event>)rsp);
                } else {
                    current_owner()->on_event(m_cur_task);
                }
            } else {
                sleep(1);
            }

            return 0;
        }

        void add_helping(ptr<plugin> plugin, ptr<cqueue<ptr<object>>> pool) {
            lock_guard<mutex> _(m_mutex);

            m_helping[plugin] = pool;
        }

        void rm_helping(ptr<plugin> plugin) {
            lock_guard<mutex> _(m_mutex);

            m_helping.erase(plugin);
        }

        long helping_count() {
            lock_guard<mutex> _(m_mutex);
            return m_helping.size();
        }

        ptr<plugin> current_owner() {
            return m_cur_owner;
        }

        ptr<object> current_task() {
            return m_cur_task;
        }

    protected:
        typedef map<ptr<plugin>, ptr<cqueue<ptr<object>>>> container;

        mutex m_mutex;
        container m_helping;

        ptr<plugin> m_cur_owner;
        ptr<event> m_cur_task;
        pthread_key_t* m_thread_context;
    };
    
}


#endif /* help_thread_h */
