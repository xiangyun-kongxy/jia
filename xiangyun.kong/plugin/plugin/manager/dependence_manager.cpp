//
//  dependence_manager.cpp
//  plugin
//
//  Created by xiangyun.kong on 10/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "dependence_manager.hpp"
#include "plugin_manager.hpp"
#include "function_manager.hpp"

#include <lib/init/initializer.hpp>
#include <lib/identifier/id_name.h>

using namespace kxy;

namespace pf {

    extern recursive_mutex g_plugin_managing_mutex;

    dependence_manager* g_dependence_manager = nullptr;

    void __uninit_dependence_manager() {
        delete g_dependence_manager;
        g_dependence_manager = nullptr;
    }
    
    void __attribute__((constructor)) __init_dependence_manager() {
        g_dependence_manager = new dependence_manager;
        
        register_uninitializer("uninitialize dependence manager",
                               __uninit_dependence_manager);
    }

    dependence_manager* dependence_manager::instance() {
        return g_dependence_manager;
    }

    dependence_manager::dependence_manager() {
    }
    
    dependence_manager::~dependence_manager() {
        m_depend.clear();
        m_be_depend.clear();
    }

    void dependence_manager::add_depend(ptr<object> obj,
                                        ptr<object> be_depend) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        if (_exist(obj, be_depend) == m_depend.end()) {
            m_depend.push_back(container::value_type(obj, be_depend));
            m_be_depend.push_back(container::value_type(be_depend, obj));
        }
    }

    void dependence_manager::rm_depend(ptr<object> obj,
                                       ptr<object> be_depend) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);
        
        container::iterator i;
        i = _exist(obj, be_depend);
        if (i != m_depend.end()) {
            m_depend.erase(i);

            for (i = m_be_depend.begin(); i != m_be_depend.end(); ++i) {
                if (_match(i->first, obj) && _match(i->second, be_depend)) {
                    m_be_depend.erase(i);
                    break;
                }
            }
        }
    }

    bool dependence_manager::is_depend_ready(ptr<kxy::object> obj) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        container::iterator i;
        for (i = m_depend.begin(); i != m_depend.end(); ++i) {
            if (_match(i->first, obj)) {
                if (!plugin_manager::instance()->check_ready(i->second) &&
                    !function_manager::instance()->check_ready(i->second)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool dependence_manager::is_depended(ptr<kxy::object> obj) {
        lock_guard<recursive_mutex> _(g_plugin_managing_mutex);

        list<ptr<object>> objs = _extern_sub_obj(obj);
        for (ptr<object> id : objs) {
            container::iterator i;
            for (i = m_be_depend.begin(); i != m_be_depend.end(); ++i) {
                if (_match(id, i->first)) {
                    if (plugin_manager::instance()->check_ready(i->second) ||
                        (i->second->is_kind_of(OBJ_IDENTIFIER) &&
                         function_manager::instance()->check_ready(i->second))) {
                        return true;
                    }
                }
            }
        }
        
        ptr<identifier> id = new id_name(obj->name());
        const plugin_info* pi = plugin_manager::instance()->find_plugin(id);
        if (pi != nullptr) {
            ptr<cqueue<ptr<object>>> tasks = pi->threads->front()->pool();
            if (tasks->size() > 0) {
                return true;
            }
        }
        
        return false;
    }

    dependence_manager::container::iterator
    dependence_manager::_exist(ptr<object> depend, ptr<object> be_depend) {
        container::iterator i;
        for (i = m_depend.begin(); i != m_depend.end(); ++i) {
            if (_match(i->first, depend) && _match(i->second, be_depend)) {
                return i;
            }
        }
        return m_depend.end();
    }
    
    bool dependence_manager::_match(ptr<object> o1, ptr<object> o2) {
        if (o1->is_kind_of(OBJ_IDENTIFIER)) {
            return ((ptr<identifier>)o1)->match(o2);
        } else if (o2->is_kind_of(OBJ_IDENTIFIER)) {
            return ((ptr<identifier>)o2)->match(o1);
        } else {
            return o1 == o2;
        }
    }
    
    list<ptr<object>> dependence_manager::_extern_sub_obj(ptr<object> obj) {
        list<ptr<object>> result;
        ptr<identifier> id = new id_name(obj->name());
        result.push_back(id);
        result.push_back(obj);
        
        const plugin_info* pi = plugin_manager::instance()->find_plugin(id);
        if (pi != nullptr) {
            list<ptr<identifier>> func;
            
            func = pi->pl->accepted_task();
            result.insert(result.end(), func.begin(), func.end());
            
            func = pi->pl->accepted_event();
            result.insert(result.end(), func.begin(), func.end());
        }
        
        return result;
    }

}
