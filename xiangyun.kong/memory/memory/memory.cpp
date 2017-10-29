//
//  memory.cpp
//  memory
//
//  Created by 孔祥云 on 1/7/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "memory.hpp"

#include <lib/fs/kv.hpp>
#include <lib/serialize/serializable.hpp>

#include <memory/executor/exe_save_barren.hpp>
#include <memory/executor/exe_load_barren.hpp>

#include <messages.hpp>

namespace mind {
    
    const string memory::m_path = "barren_memory";
    
    memory::memory() {
        m_executors[M_LOAD_BARREN] = new load_barren;
        m_executors[M_SAVE_BARREN] = new save_barren;
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
