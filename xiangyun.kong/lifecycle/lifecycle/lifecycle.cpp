//
//  lifecycle.cpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include "lifecycle.hpp"
#include "trigger/trigger_start_framework.hpp"
#include "trigger/trigger_load_plugin.hpp"

#include <functions.h>
#include <names.h>
#include <events.h>

namespace pf{
    
    lifecycle::lifecycle() {
        m_event_processor[EVT_START_FRAMEWORK] = new start_framework;
        m_event_processor[EVT_LOAD_PLUGIN] = new load_plugin;
    }

    lifecycle::~lifecycle() {
        map<char*, list<config*>>::iterator i;
        for (i = m_configs.begin(); i != m_configs.end(); ++i) {
            delete[] i->first;

            for (config* conf : i->second) {
                delete conf;
            }
        }
    }
    
    string lifecycle::type() const {
        return PLUGIN_LIFECYCLE;
    }
    
    bool lifecycle::is_kind_of(const string &type_name) const {
        return type_name == PLUGIN_LIFECYCLE || plugin::is_kind_of(type_name);
    }

    void lifecycle::set_config(char* buf, const list<config*>& configs) {
        m_configs[buf] = configs;
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
