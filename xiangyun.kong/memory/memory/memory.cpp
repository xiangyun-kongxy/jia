//
//  memory.cpp
//  memory
//
//  Created by 孔祥云 on 1/7/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "memory.hpp"

#include <lib/fs/kv.h>
#include <lib/serialize/serializable.hpp>

#include <memory/trigger/trigger_save_barren.h>
#include <memory/executor/exe_load_barren.h>

#include <functions.h>
#include <events.h>

namespace mind {
    
    const string memory::m_path = "barren_memory";
    
    memory::memory() {
        m_executors[F_LOAD_BARREN] = new load_barren;
        m_triggers[EVT_SAVE_BARREN] = new save_barren;
    }
    
    void memory::write(ptr<barren> barren) {
        serializable ar;
        ar << **barren;
        kv_put(m_path, l2s(barren->id()), ar.buf());
    }
    
    ptr<barren> memory::read(long id) {
        string buf = kv_get(m_path, l2s(id));
        if (buf.length() > 0) {
            serializable ar(buf.c_str());
            ptr<barren> b = new barren(false);
            ar >> **b;
            return b;
        }
        return nullptr;
    }

    extern "C" void* init_memory(void* conf) {
        memory* plugin = new memory;
        return plugin;
    }
}
