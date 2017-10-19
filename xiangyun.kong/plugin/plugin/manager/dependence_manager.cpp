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

#include <lib/lock/auto_lock.h>


namespace pf {

    dependence_manager* g_dependence_manager = nullptr;

    void __attribute__((constructor)) __init_dependence_manager() {
        g_dependence_manager = new dependence_manager;
    }

    dependence_manager* dependence_manager::instance() {
        return g_dependence_manager;
    }

    dependence_manager::dependence_manager() {
        pthread_mutex_init(&m_mutex, nullptr);
    }

    void dependence_manager::add_depend(ptr<object> obj,
                                        ptr<object> be_depend) {
        auto_lock _(&m_mutex);

        if (_exist(obj, be_depend) == m_depend.end()) {
            m_depend.push_back(container::value_type(obj, be_depend));
            m_be_depend.push_back(container::value_type(be_depend, obj));
        }
    }

    void dependence_manager::rm_depend(ptr<object> obj,
                                       ptr<object> be_depend) {
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
        container::iterator i;
        for (i = m_be_depend.begin(); i != m_be_depend.end(); ++i) {
            if (_match(obj, i->first)) {
                if (plugin_manager::instance()->check_ready(i->second) ||
                    function_manager::instance()->check_ready(i->second)) {
                    return true;
                }
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

}
