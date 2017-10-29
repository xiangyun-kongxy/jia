//
// Created by xiangyun.kong on 8/8/16.
//

#include "plugin.hpp"

#include <lib/identifier/id_name.hpp>

#include <plugin/manager/thread_manager.hpp>
#include <plugin/manager/plugin_manager.hpp>
#include <plugin/response/simple_response.hpp>
#include <plugin/event/simple_event.hpp>

#include <errors.hpp>

#include <pthread.h>
#include <iostream>

using namespace kxy;
using namespace std;

namespace pf {
    
    ptr<plugin> g_lifecycle = nullptr;
    ptr<plugin> g_bus = nullptr;
    ptr<plugin> g_ps = nullptr;

    plugin::plugin() {
        m_status = PS_LOADING;

        m_status = PS_LOADED;
    }

    ptr<response> plugin::do_task(ptr<event> evt) {
        ptr<executor> executor = nullptr;
        if (evt != nullptr) {
            executor = m_executors[evt->name()];
            if (executor != nullptr)
                return executor->run(this, evt);
        }
        return new simple_response(evt, EC_TASK_NOT_SUPPORTED,
                                   EM_TASK_NOT_SUPPORTED);
    }

    list<ptr<identifier>> plugin::depend_on() const {
        return list<ptr<identifier>>();
    }

    list<ptr<identifier>> plugin::supported_event() const {
        list<ptr<identifier>> evt;
        
        map<string,ptr<executor>>::const_iterator it;
        for(it = m_executors.begin(); it != m_executors.end(); ++it)
            evt.push_back(new id_name(it->first));
        
        return evt;
    }

    ptr<plugin> plugin::current_plugin() {
        return thread_manager::instance()->current_plugin();
    }
    
    ptr<event> plugin::current_task() {
        return thread_manager::instance()->current_task();
    }

    void plugin::init() {
        lock_guard<mutex> _(m_mutex);

        m_status = PS_INSTALLING;
        
        m_tasks = new cqueue<ptr<object>>;
        
        thread_manager* tm = thread_manager::instance();
        m_threads.push_back(tm->create_thread_for_plugin(this));
        
        plugin_manager* pm = plugin_manager::instance();
        pm->add_plugin(this);

        m_status = PS_INSTALLED;
    }

    void plugin::suspend() {
        lock_guard<mutex> _(m_mutex);

        plugin_manager* pm = plugin_manager::instance();
        pm->plugin_suspended(this);

        thread_manager* tm = thread_manager::instance();
        for (pthread_t thread : m_threads) {
            tm->suspend_thread(thread);
        }

        m_status = PS_INSTALLED;
    }

    void plugin::resume() {
        lock_guard<mutex> _(m_mutex);

        thread_manager* tm = thread_manager::instance();
        for (pthread_t thread : m_threads) {
            tm->resume_thread(thread);
        }

        plugin_manager* pm = plugin_manager::instance();
        pm->plugin_actived(this);

        m_status = PS_RUNNING;
    }

    void plugin::uninit() {
        lock_guard<mutex> _(m_mutex);

        m_status = PS_UNINSTALLING;

        thread_manager* tm = thread_manager::instance();
        for (pthread_t thread : m_threads) {
            tm->delete_thread(thread);
        }
        m_threads.clear();

        plugin_manager* pm = plugin_manager::instance();
        pm->rm_plugin(this);

        m_status = PS_UNINSTALLED;
    }

    plugin_status plugin::status() {
        return m_status;
    }

    ptr<cqueue<ptr<object>>> plugin::tasks() {
        return m_tasks;
    }

    void plugin::inc_thread() {
        lock_guard<mutex> _(m_mutex);

        thread_manager* tm = thread_manager::instance();
        pthread_t thread_id = tm->create_thread_for_plugin(this);
        m_threads.push_back(thread_id);

        if (m_status == PS_RUNNING) {
            tm->resume_thread(thread_id);
        }
    }

    void plugin::dec_thread() {
        lock_guard<mutex> _(m_mutex);

        if (m_threads.size() > 1) {
            pthread_t thread_id = m_threads.front();
            m_threads.pop_front();

            thread_manager* tm = thread_manager::instance();
            tm->delete_thread(thread_id);
        }
    }
}
