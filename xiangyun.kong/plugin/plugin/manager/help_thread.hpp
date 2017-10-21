//
//  help_thread.hpp
//  plugin
//
//  Created by xiangyun.kong on 10/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef help_thread_h
#define help_thread_h

#include <unistd.h>

#include <lib/thread/thread.h>
#include <lib/container/cqueue.h>

#include <plugin/response/response.h>
#include <plugin/event/event.h>
#include <plugin/task/task.h>
#include <plugin/event/simple_event.h>
#include <plugin/plugin/plugin.h>

#include <events.h>

#include <mutex>

using namespace std;
using namespace kxy;

namespace pf {

    class help_thread : public thread {
    public:
        DECLARE_TYPE(thread, OBJ_HELP_THREAD);

    public:
        virtual void* run_once() override {
            m_cur_task = nullptr;
            do {
                lock_guard<mutex> _(m_mutex);

                m_cur_owner = nullptr;
                
                container::iterator i;
                for (i = m_helping.begin(); i != m_helping.end(); ++i) {
                    m_cur_task = i->second->try_pop();
                    if (m_cur_task != nullptr) {
                        m_cur_owner = i->first;
                        break;
                    }
                }
            } while (0);

            if (m_cur_task != nullptr) {
                if (m_cur_task->is_kind_of(OBJ_TASK)) {
                    ptr<response> rsp = current_owner()->do_task(m_cur_task);

                    extern ptr<plugin> g_bus;
                    ptr<serializable> data;
                    ptr<simple_event> evt;
                    data = new serializable;
                    data << rsp;
                    evt = new simple_event(EVT_RESPONSE, data);
                    g_bus->on_event(evt);
                } else if (m_cur_task->is_kind_of(OBJ_EVENT)) {
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

        container m_helping;
        ptr<plugin> m_cur_owner;
        ptr<object> m_cur_task;
        mutex m_mutex;
    };

}

#endif /* help_thread_h */
