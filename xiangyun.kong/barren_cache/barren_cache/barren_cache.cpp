//
//  barren_cache.cpp
//  barren_cache
//
//  Created by 孔祥云 on 1/13/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "barren_cache.hpp"
#include <identifier/id_name.h>
#include <memory/memory_function.h>
#include <task/simple_task.h>
#include <event/simple_event.h>
#include <bus/ipc.hpp>
#include "trigger/trigger_on_put_barren.h"
#include "executor/exe_on_get_barren.h"
#include "cache_function.h"

namespace mind {
    
    barren_cache::barren_cache() {
        m_provider = new id_name("memory");
        // TODO: capacity from config
        m_cache = new cache(640000);
        
        m_event_processor[F_ON_PUT_BARREN] = new trigger_on_put_barren();
        m_task_processor[F_ON_GET_BARREN] = new exe_on_get_barren();
    }
    
    ptr<barren> barren_cache::get_barren(long id) {
        ptr<barren> obj = m_cache->get(id);
        if(obj == nullptr) {
            obj = load_barren(id);
            if(obj != nullptr) {
                m_cache->put(obj);
            }
        }
        return obj;
    }
    
    void barren_cache::put_barren(ptr<barren> obj) {
        save_barren(obj);
        
        ptr<barren> existed = m_cache->get(obj->id());
        if(existed == nullptr) {
            m_cache->put(obj);
        }
    }
    
    ptr<barren> barren_cache::load_barren(long id) {
        ptr<serializable> rsp = call_plugin(m_provider, F_ON_LOAD_BARREN, id);
        ptr<barren> barren = nullptr;
        if (rsp != nullptr) {
            rsp >> barren;
        }
        return barren;
    }
    
    void barren_cache::save_barren(ptr<barren> obj) {
        ptr<serializable> param;
        param << obj;
        ptr<event> evt = new simple_event(F_ON_SAVE_BARREN, param, m_provider);
        send_message(evt);
    }
    
    string barren_cache::type() const {
        return "barren_cache";
    }
    
    bool barren_cache::is_kind_of(const string &type_name) const {
        return type_name == "barren_cache" || plugin::is_kind_of(type_name);
    }

    extern "C" void* init_barren_cache(void* conf) {
        ptr<barren_cache> plugin = new barren_cache;
        return *plugin;
    }
}
