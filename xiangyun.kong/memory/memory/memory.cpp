//
//  memory.cpp
//  memory
//
//  Created by 孔祥云 on 1/7/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "memory.hpp"
#include "memory_function.h"
#include "trigger/trigger_on_save_barren.h"
#include "executor/exe_on_load_barren.h"
#include <fs/kv.h>
#include <convert/basic_type_convert.h>

namespace mind {
    
    const string memory::m_path = "barren_memory";
    
    memory::memory() {
        m_task_processor[F_ON_LOAD_BARREN] = new exe_on_load_barren;
        m_event_processor[F_ON_SAVE_BARREN] = new trigger_on_save_barren;
    }
    
    string memory::type() const {
        return "memory";
    }
    
    bool memory::is_kind_of(const string &type_name) const {
        return "memory" == type_name || plugin::is_kind_of(type_name);
    }
    
    void memory::write(ptr<barren> barren) {
        serializable ar;
        ar << **barren;
        kv_put(m_path, l2s(barren->id()), ar.buf());
    }
    
    ptr<barren> memory::read(const string &id) {
        serializable ar(kv_get(m_path, id).c_str());
        ptr<barren> b = new barren();
        ar >> **b;
        return b;
    }

    extern "C" void* init_memory(void* conf) {
        ptr<memory> plugin = new memory;
        return *plugin;
    }
}
