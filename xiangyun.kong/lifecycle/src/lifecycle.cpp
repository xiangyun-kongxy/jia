//
//  lifecycle.cpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include "lifecycle.hpp"
#include "executor/exe_load_plugin.h"

#include <functions.h>

namespace pf{
    
    lifecycle::lifecycle() {
        m_task_processor[F_LOAD_PLUGIN] = new load_plugin();
    }
    
    string lifecycle::type() const {
        return PLUGIN_LIFECYCLE;
    }
    
    bool lifecycle::is_kind_of(const string &type_name) const {
        return type_name == PLUGIN_LIFECYCLE || plugin::is_kind_of(type_name);
    }

    void lifecycle::update_object(ptr<object> obj, plugin_status status) {
        map<ptr<object>, plugin_status>::iterator i;

        switch (status) {
            case PS_LOADING:
                m_objects[obj] = PS_LOADING;
                break;
            case PS_LOADED:
                remove_identifier(obj);
                if (is_satisfied(obj)) {
                    m_objects[obj] = PS_INSTALLING;
                } else {
                    m_objects[obj] = PS_LOADED;
                }
                break;
            case PS_INSTALLING:
                m_objects[obj] = PS_INSTALLING;
                break;
            case PS_RUNNING:
                m_objects[obj] = PS_RUNNING;
                if (obj->is_kind_of(OBJ_PLUGIN)) {
                    ptr<plugin> plugin = obj;
                    for (ptr<identifier> id : plugin->accepted_task()) {
                        m_objects[id] = PS_RUNNING;
                    }
                    for (ptr<identifier>id : plugin->accepted_event()) {
                        m_objects[id] = PS_RUNNING;
                    }
                }

                for (i = m_objects.begin(); i != m_objects.end(); ++i) {
                    if (i->second == PS_LOADED &&
                        i->first->is_kind_of(OBJ_PLUGIN) &&
                        is_satisfied(i->first)) {
                        i->second = PS_INSTALLING;
                    }
                }
                
                break;
            case PS_UPGRADING:
                break;
            case PS_UPDATING_DEPENDENCE:
                break;
            case PS_UNLOADING:
                break;
            case PS_READY:
                break;
            default:
                m_objects[obj] = PS_UNKNOWN;
        }
    }

    list<ptr<object>> lifecycle::get_object(const string& type,
                                            plugin_status status) {
        list<ptr<object>> result;
        map<ptr<object>, plugin_status>::iterator i;
        for (i = m_objects.begin(); i != m_objects.end(); ++i) {
            if (i->second == status && i->first->is_kind_of(type)) {
                result.push_back(i->first);
            }
        }
        
        return result;
    }

    void lifecycle::remove_identifier(ptr<plugin> plugin) {
        map<ptr<object>, plugin_status>::iterator i;
        for (i = m_objects.begin(); i != m_objects.end(); ++i) {
            if (i->first->is_kind_of(OBJ_IDENTIFIER) &&
                ((ptr<identifier>)i->first)->match(plugin)) {
                m_objects.erase(i);
                break;
            }
        }
    }

    bool lifecycle::is_satisfied(ptr<plugin> plugin) {
        list<ptr<identifier>> dependences = plugin->depend_on();
        list<ptr<identifier>>::iterator i;
        for (i = dependences.begin(); i != dependences.end(); ++i) {
            if (get_object_status(*i) != PS_RUNNING) {
                return false;
            }
        }
        return true;
    }

    plugin_status lifecycle::get_object_status(ptr<identifier> id) {
        map<ptr<object>, plugin_status>::iterator i;
        for (i = m_objects.begin(); i != m_objects.end(); ++i) {
            if (id->match(i->first)) {
                return i->second;
            }
        }
        return PS_UNKNOWN;
    }
    
}
