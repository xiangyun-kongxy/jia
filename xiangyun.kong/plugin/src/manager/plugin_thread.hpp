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

#include <thread/thread.h>
#include <response/response.h>
#include <event/event.h>
#include <task/task.h>
#include <event/simple_event.h>
#include <container/cqueue.h>
#include <plugin/plugin.h>
#include <unistd.h>

using namespace std;
using namespace kxy;

namespace pf {

    class plugin_thread : public thread {
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
            } else if (tsk->is_kind_of("task")) {
                ptr<response> rsp = m_owner->do_task((ptr<task>)tsk);

                extern ptr<plugin> g_bus;
                ptr<serializable> data;
                ptr<simple_event> evt;
                data = new serializable;
                data << tsk << rsp;
                evt = new simple_event("response", data);
                g_bus->on_event(evt);
            } else if (tsk->is_kind_of("event")) {
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

    public:
        virtual bool is_kind_of(const string &name) const override {
            return name == "plugin_thread" || thread::is_kind_of(name);
        }

        virtual string type() const override {
            return "plugin_thread";
        }

    protected:
        ptr<cqueue<ptr<object>>> m_pool;
        ptr<plugin> m_owner;
    };

}

#endif //PLUGIN_TASK_THREAD_H
