//
//  lifecycle.cpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include "lifecycle.hpp"
#include "trigger/trigger_start_framework.hpp"
#include "trigger/trigger_stop_framework.hpp"
#include "trigger/trigger_load_plugin.hpp"
#include "trigger/trigger_unload_plugin.hpp"

#include <functions.h>
#include <names.h>
#include <events.h>

#include <iostream>

using namespace std;

namespace pf{
    
    lifecycle::lifecycle() {
        m_event_processor[EVT_START_FRAMEWORK] = new start_framework;
        m_event_processor[EVT_STOP_FRAMEWORK] = new stop_framework;
        m_event_processor[EVT_LOAD_PLUGIN] = new load_plugin;
        m_event_processor[EVT_UNLOAD_PLUGIN] = new unload_plugin;
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
    
    void lifecycle::set_config(char* buf, const list<config*>& configs) {
        m_configs[buf] = configs;
    }

}
