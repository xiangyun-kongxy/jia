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

#include <lib/identifier/id_name.hpp>
#include <lib/serialize/serializable.hpp>
#include <lib/convert/type_convert.hpp>

#include <id_service/executor/exe_fetch_add_guid.hpp>
#include <id_service/executor/exe_fetch_add_guid_bench.hpp>
#include <id_service/executor/exe_get_cur_guid.hpp>
#include <id_service/executor/exe_set_guid.hpp>


#include <ipc.hpp>
#include <messages.hpp>
#include <config_keys.hpp>


namespace kxy {
    
    id_service::id_service() {
        m_cur_id = 0L;
        
        m_executors[M_FETCH_ADD_GUID]       = new class fetch_add_guid;
        m_executors[M_FETCH_ADD_GUID_BENCH] = new fetch_add_guid_bench;
        m_executors[M_GET_CUR_GUID]         = new class get_cur_guid;
        m_executors[M_SET_GUID]             = new class set_guid;
    }
    
    void id_service::resume() {
        plugin::resume();
        
        load_guid();
    }
    
    void id_service::uninit() {
        save_guid();

        plugin::uninit();
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
    
    long id_service::fetch_add_guid(long size) {
        return atomic_fetch_add(&m_cur_id, size);
    }

    void id_service::load_guid() {
        ptr<serializable> rsp;
        rsp = call_plugin(new id_name(PLUGIN_CONFIG_CENTER), M_GET_CONFIG,
                          CFG_CUR_GUID);
        if (rsp != nullptr) {
            string id;
            rsp >> id;
            set_guid(s2l(id.c_str()));
        }
    }
    
    void id_service::save_guid() {
        send_to(new id_name(PLUGIN_CONFIG_CENTER), M_PUT_CONFIG,
                CFG_CUR_GUID, l2s(get_guid()));
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

