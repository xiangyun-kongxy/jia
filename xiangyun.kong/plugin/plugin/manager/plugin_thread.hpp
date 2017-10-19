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
#include <plugin/task/task.h>
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
        }

        virtual ~plugin_thread() {

        }

    public:
        virtual void* run_once() override {
            ptr<object> tsk = m_pool->pop();
            if(tsk == nullptr) {
                usleep(12);
            } else if (tsk->is_kind_of(OBJ_TASK)) {
                ptr<response> rsp = m_owner->do_task((ptr<task>)tsk);

                extern ptr<plugin> g_bus;
                ptr<serializable> data;
                ptr<simple_event> evt;
                data = new serializable;
                data << tsk << rsp;
                evt = new simple_event(EVT_RESPONSE, data);
                g_bus->on_event(evt);
            } else if (tsk->is_kind_of(OBJ_EVENT)) {
                m_owner->on_event((ptr<event>)tsk);
            }
            return 0;
        }

        ptr<cqueue<ptr<object>>> pool() const {
            return m_pool;
        }

        ptr<plugin> owner() const {
            return m_owner;
        }

    protected:
        ptr<cqueue<ptr<object>>> m_pool;
        ptr<plugin> m_owner;
    };

}

#endif //PLUGIN_TASK_THREAD_H
