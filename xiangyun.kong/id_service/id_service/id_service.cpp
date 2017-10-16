/*
 *  id_service.cpp
 *  id_service
 *
 *  Created by 孔祥云 on 10/14/17.
 *  Copyright © 2017 孔祥云. All rights reserved.
 *
 */

#include "id_service.hpp"

#include <iostream>

#include <lib/identifier/id_name.h>
#include <lib/serialize/serializable.hpp>

#include <id_service/executor/exe_fetch_add_guid.hpp>
#include <id_service/executor/exe_get_cur_guid.hpp>
#include <id_service/trigger/trigger_set_guid.h>


#include <ipc.hpp>
#include <functions.h>
#include <events.h>
#include <predefined_barren.h>

namespace kxy {
    
    id_service::id_service() {
        m_cur_id = BARREN_FREE_BEGIN;
        load_guid();
        
        m_task_processor[F_FETCH_ADD_GUID] = new class fetch_add_guid;
        m_task_processor[F_GET_CUR_CUID] = new class get_cur_guid;

        m_event_processor[EVT_SET_GUID] = new class set_guid;
    }
    
    id_service::~id_service() {
        save_guid();
    }
    
    void id_service::set_guid(long id) {
        if (id > m_cur_id) {
            m_cur_id = id;
        }
    }
    
    long id_service::get_guid() {
        return m_cur_id;
    }
    
    long id_service::fetch_add_guid() {
        return m_cur_id++;
    }
    
    void id_service::load_guid() {
        ptr<serializable> rsp;
        rsp = call_plugin(new id_name(PLUGIN_CONFIG_CENTER), F_GET_CONFIG, CFG_CUR_GUID);
        if (rsp != nullptr) {
            long id = 0;
            rsp >> id;
            set_guid(id);
        }
    }
    
    void id_service::save_guid() {
        send_to(new id_name(PLUGIN_CONFIG_CENTER), EVT_PUT_CONFIG, CFG_CUR_GUID);
    }
    
    string id_service::type() const {
        return PLUGIN_ID_SERVICE;
    }
    
    bool id_service::is_kind_of(const string &type_name) const {
        return type_name == PLUGIN_ID_SERVICE || plugin::is_kind_of(type_name);
    }
    
    extern "C" {
        void* init_id_service(void* config) {
            id_service* service = new id_service;
            
            if (config != nullptr) {
                xml_node<>* param = (xml_node<>*)config;
                xml_attribute<>* attr = param->first_attribute(CFG_CUR_GUID.c_str());
                if (attr != nullptr) {
                    service->set_guid(atol(attr->value()));
                }
            }
                
            return service;
        }
    }
}

