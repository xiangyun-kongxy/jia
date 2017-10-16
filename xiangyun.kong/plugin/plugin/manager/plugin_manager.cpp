//
//  plugin_manager.cpp
//  plugin
//
//  Created by xiangyun.kong on 10/3/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "plugin_manager.hpp"

namespace pf {

    ptr<plugin_manager> g_plugin_manager = nullptr;

    ptr<plugin_manager> plugin_manager::instance() {
        if (g_plugin_manager == nullptr) {
            g_plugin_manager = new plugin_manager;
        }
        return g_plugin_manager;
    }

    void plugin_manager::add_plugin(ptr<plugin> p) {
        if (m_container.find(p) == m_container.end()) {
            ptr<cqueue<ptr<object>>> msg_queue = new cqueue<ptr<object>>;
            ptr<plugin_thread> thread = new plugin_thread(msg_queue, p);
            thread->start();

            list<ptr<plugin_thread>> threads;
            threads.push_back(thread);
            m_container[p] = threads;
            m_thread_index[thread->thread_id()] = p;
        }
    }

    void plugin_manager::delete_plugin(ptr<plugin> p) {
        container_type::iterator i;
        i = m_container.find(p);
        if (i != m_container.end()) {
            list<ptr<plugin_thread>>::iterator j;
            for (j = i->second.begin(); j != i->second.end(); ++j) {
                (*j)->stop();
                m_thread_index.erase((*j)->thread_id());
            }
            m_container.erase(i);
        }
    }

    list<ptr<plugin>> plugin_manager::find_plugin(ptr<identifier> id) {
        list<ptr<plugin>> plugins;
        container_type::iterator i;
        for (i = m_container.begin(); i != m_container.end(); ++i) {
            if (id->match(i->first)) {
                plugins.push_back(i->first);
            }
        }
        return plugins;
    }

    list<ptr<plugin>> plugin_manager::get_all_plugin() {
        list<ptr<plugin>> plugins;
        container_type::iterator i;
        for (i = m_container.begin(); i != m_container.end(); ++i) {
            plugins.push_back(i->first);
        }
        return plugins;
    }

    void plugin_manager::set_plugin_thread_count(ptr<plugin> p, long count) {
        container_type::iterator i;
        i = m_container.find(p);
        if (i != m_container.end()) {
            ptr<cqueue<ptr<object>>> msg_queue = i->second.front()->pool();
            while (i->second.size() < count) {
                ptr<plugin_thread> thread = new plugin_thread(msg_queue, p);
                thread->start();
                i->second.push_back(thread);
                m_thread_index[thread->thread_id()] = p;
            }
            while (i->second.size() > count) {
                ptr<plugin_thread> thread = i->second.front();
                thread->stop();
                m_thread_index.erase(thread->thread_id());
                i->second.pop_front();
            }
        }
    }

    long plugin_manager::get_plugin_thread_count(ptr<plugin> p) {
        container_type::iterator i;
        i = m_container.find(p);
        if (i != m_container.end()) {
            return i->second.size();
        }
        return 0L;
    }
    
    list<ptr<plugin_thread>> plugin_manager::get_plugin_thread(ptr<plugin> p) {
        container_type::iterator i;
        i = m_container.find(p);
        if (i != m_container.end()) {
            return i->second;
        }
        return list<ptr<plugin_thread>>();
    }

    ptr<plugin> plugin_manager::get_plugin_by_thread_id(pthread_t thread_id) {
        map<pthread_t, ptr<plugin>>::iterator i;
        i = m_thread_index.find(thread_id);
        if (i != m_thread_index.end()) {
            return i->second;
        }
        return nullptr;
    }
}
