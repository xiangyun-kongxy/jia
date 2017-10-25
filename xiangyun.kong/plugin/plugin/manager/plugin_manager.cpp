//
//  plugin_manager.cpp
//  plugin
//
//  Created by xiangyun.kong on 10/3/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "plugin_manager.hpp"
#include "function_manager.hpp"
#include "dependence_manager.hpp"

#include <lib/init/initializer.hpp>

#include <iostream>

using namespace std;
using namespace kxy;

namespace pf {

    recursive_mutex g_plugin_managing_mutex;
    
    plugin_manager* g_plugin_manager = nullptr;

#define HELP_THREAD_COUNT   8
    
    void __uninit_plugin_manager() {
        delete g_plugin_manager;
        g_plugin_manager = nullptr;
    }
    
    void __attribute__((constructor)) __init_plugin_manager() {
        g_plugin_manager = new plugin_manager;
        
        register_uninitializer("uninitialize plugin manager", __uninit_plugin_manager);
    }

    plugin_manager* plugin_manager::instance() {
        return g_plugin_manager;
    }
    
    plugin_manager::plugin_manager() {
        for (long i = 0; i < HELP_THREAD_COUNT; ++i) {
            ptr<help_thread> helper = new help_thread;
            helper->start();
            
            m_task_helper.push_back(helper);
            m_threads[helper->thread_id()] = helper;
        }
        
        m_version = 1;
    }
    
    plugin_manager::~plugin_manager() {
        for (ptr<help_thread> thread : m_task_helper) {
            thread->stop(true);
            m_threads.erase(thread->thread_id());
        }
        m_task_helper.clear();
        ++m_version;
    }
    
    void plugin_manager::add_plugin(ptr<plugin> pl) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        list<plugin_info*>::iterator i;
        for (i = m_plugins.begin(); i != m_plugins.end(); ++i) {
            if (**i == pl)
                break;
        }
        if (i == m_plugins.end()) {
            plugin_info* pi = new plugin_info;
            pi->pl = pl;
            pi->is_active = false;
            pi->threads = new list<ptr<plugin_thread>>;
            pi->threads->push_back(_create_thread(pl));
            m_plugins.push_back(pi);

            for (ptr<identifier> function : pl->supported_event()) {
                function_manager::instance()->add_function(pl, function);
            }
            for (ptr<identifier> obj : pl->depend_on()) {
                dependence_manager::instance()->add_depend(pl, obj);
            }
            
            ++m_version;
        } else {
            cout << "error: plugin " << pl->name() << " duplicated." << endl;
        }
    }

    void plugin_manager::rm_plugin(ptr<identifier> id) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        list<plugin_info*>::iterator i;
        for (i = m_plugins.begin(); i != m_plugins.end(); ++i) {
            if (**i == id)
                break;
        }
        if (i != m_plugins.end()) {
            ptr<plugin> pl = (*i)->pl;
            for (ptr<help_thread> helper : m_task_helper) {
                helper->rm_helping(pl);
            }
            for (ptr<identifier> function : pl->supported_event()) {
                function_manager::instance()->rm_function(function);
            }
            for (ptr<identifier> obj : pl->depend_on()) {
                dependence_manager::instance()->rm_depend(pl, obj);
            }

            for (ptr<plugin_thread> thread : *(*i)->threads) {
                m_threads.erase(thread->thread_id());
            }
            delete (*i)->threads;
            delete *i;

            m_plugins.erase(i);
            ++m_version;
        }
    }

    const plugin_info* plugin_manager::find_plugin(ptr<identifier> id) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);
        
        list<plugin_info*>::iterator i;
        for (i = m_plugins.begin(); i != m_plugins.end(); ++i) {
            if (**i == id)
                break;
        }
        if (i != m_plugins.end()) {
            return *i;
        }
        return nullptr;
    }

    list<plugin_info*> plugin_manager::get_all_plugin() {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        return m_plugins;
    }

    void plugin_manager::active_plugin(ptr<identifier> id) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        if (dependence_manager::instance()->is_depend_ready(id)) {
            list<plugin_info*>::iterator i;
            for (i = m_plugins.begin(); i != m_plugins.end(); ++i) {
                if (**i == id)
                    break;
            }
            if (i != m_plugins.end()) {
                for (ptr<plugin_thread> thread : *(*i)->threads) {
                    thread->start();
                }

                for (ptr<identifier> function : (*i)->pl->supported_event()) {
                    function_manager::instance()->active_function(function);
                }
                
                if (!(*i)->pl->is_kind_of(PLUGIN_BUS)) {
                    for (ptr<help_thread> helper : m_task_helper) {
                        helper->add_helping((*i)->pl, (*i)->threads->front()->pool());
                    }
                }

                (*i)->is_active = true;
                ++m_version;
            }
        }
    }
    
    void plugin_manager::suspend_plugin(ptr<identifier> id) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        list<plugin_info*>::iterator i;
        for (i = m_plugins.begin(); i != m_plugins.end(); ++i) {
            if (**i == id)
                break;
        }
        if (i != m_plugins.end()) {
            for (ptr<help_thread> helper : m_task_helper) {
                helper->rm_helping((*i)->pl);
            }
            
            for (ptr<identifier> function : (*i)->pl->supported_event()) {
                function_manager::instance()->suspend_function(function);
            }

            for (ptr<plugin_thread> thread : *(*i)->threads) {
                thread->pause();
            }

            (*i)->is_active = false;
            
            ++m_version;
        }
    }

    context_info plugin_manager::get_context_by_thread_id(pthread_t thread_id) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        context_info ci;

        map<pthread_t, ptr<thread>>::iterator i;
        i = m_threads.find(thread_id);
        if (i != m_threads.end()) {
            if (i->second->is_kind_of(OBJ_PLUGIN_THREAD)) {
                ci.plugin = ((ptr<plugin_thread>)i->second)->owner();
                ci.task = ((ptr<plugin_thread>)i->second)->cur_task();
            } else {
                ci.plugin = ((ptr<help_thread>)i->second)->current_owner();
                ci.task = ((ptr<help_thread>)i->second)->current_task();
            }
        }
        
        return ci;
    }

    bool plugin_manager::have_task(ptr<identifier> id) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        list<plugin_info*>::iterator i;
        for (i = m_plugins.begin(); i != m_plugins.end(); ++i) {
            if (**i == id)
                break;
        }
        if (i != m_plugins.end()) {
            return (*i)->threads->front()->pool()->size() > 0;
        }
        return false;
    }

    bool plugin_manager::check_ready(ptr<kxy::identifier> id)  {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        list<plugin_info*>::iterator i;
        for (i = m_plugins.begin(); i != m_plugins.end(); ++i) {
            if (**i == id)
                break;
        }
        if (i != m_plugins.end()) {
            return (*i)->is_active;
        }
        return false;
    }
    
    long plugin_manager::version() const {
        return m_version;
    }
    
    void plugin_manager::lock() {
        g_plugin_managing_mutex.lock();
    }
    
    void plugin_manager::unlock() {
        g_plugin_managing_mutex.unlock();
    }

    ptr<plugin_thread> plugin_manager::_create_thread(ptr<plugin> pl) {
        ptr<cqueue<ptr<object>>> pool = new cqueue<ptr<object>>;
        ptr<plugin_thread> thread = new plugin_thread(pool, pl);

        if (!pl->is_kind_of(PLUGIN_BUS)) {
            for (ptr<help_thread> helper : m_task_helper) {
                helper->add_helping(pl, pool);
            }
        }
        
        m_threads[thread->thread_id()] = thread;
        
        return thread;
    }
}
