/**
 * copyright @2016. all rights reserved.
 *
 * @since:  14:25 8/12/16
 * @author: xiangyun kong
 *
 * description:
 *
 */

#ifndef PLUGIN_PLUGIN_THREAD_H
#define PLUGIN_PLUGIN_THREAD_H

#include <unistd.h>

#include <lib/thread/thread.h>
#include <lib/container/cqueue.h>

#include <plugin/response/response.h>
#include <plugin/event/event.h>
#include <plugin/event/simple_event.h>
#include <plugin/plugin/plugin.h>

#include <events.h>

using namespace std;
using namespace kxy;

namespace pf {

    class plugin_thread : public thread {
    public:
        DECLARE_TYPE(thread, OBJ_PLUGIN_THREAD);
        
    public:
        plugin_thread(ptr<cqueue<ptr<object>>> pool, ptr<plugin> owner) {
            m_owner = owner;
            m_pool = pool;
            m_cur_task = nullptr;
        }

        virtual ~plugin_thread() {

        }

    public:
        virtual void* run_once() override {
            m_cur_task = m_pool->pop();
            
            if(m_cur_task == nullptr) {
                usleep(12);
            } else if (m_cur_task->should_response()) {
                ptr<response> rsp = m_owner->do_task(m_cur_task);

                extern ptr<plugin> g_bus;
                g_bus->on_event((ptr<event>)rsp);
            } else {
                m_owner->on_event(m_cur_task);
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
    };

}

#endif //PLUGIN_TASK_THREAD_H
