//
//  barren_cache.cpp
//  barren_cache
//
//  Created by 孔祥云 on 1/13/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "barren_cache.hpp"

#include <barren_cache/executor/exe_save_cache_barren.hpp>
#include <barren_cache/executor/exe_load_cache_barren.hpp>

#include <messages.hpp>
#include <ipc.hpp>

namespace mind {
    
    barren_cache::barren_cache() {
        m_provider = new id_name(PLUGIN_MEMORY);
        // TODO: capacity from config
        m_cache = new cache(640000);
        
        m_executors[M_SAVE_CACHE_BARREN] = new class save_cache_barren;
        m_executors[M_LOAD_CACHE_BARREN] = new class load_cache_barren;
    }
    
    ptr<barren> barren_cache::load_barren(long id) {
        ptr<barren> obj = m_cache->get(id);
        if(obj == nullptr) {
            obj = load_barren_from_memory(id);
            if(obj != nullptr) {
                m_cache->put(obj);
            }
        }
        return obj;
    }
    
    void barren_cache::save_barren(ptr<barren> obj) {
        save_barren_to_memory(obj);
        
        ptr<barren> existed = m_cache->get(obj->id());
        if(existed == nullptr) {
            m_cache->put(obj);
        }
    }
    
    ptr<barren> barren_cache::load_barren_from_memory(long id) {
        ptr<serializable> rsp = call_plugin(m_provider, M_LOAD_BARREN, id);
        ptr<barren> barren = nullptr;
        if (rsp != nullptr) {
            rsp >> barren;
        }
        return barren;
    }
    
    void barren_cache::save_barren_to_memory(ptr<barren> obj) {
        send_to(m_provider, M_SAVE_BARREN, obj);
    }
    
    extern "C" void* init_barren_cache(void* conf) {
        barren_cache* plugin = new barren_cache;
        return plugin;
    }
}
