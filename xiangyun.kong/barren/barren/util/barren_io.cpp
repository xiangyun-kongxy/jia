//
//  barren_io.cpp
//  barren
//
//  Created by 孔祥云 on 1/13/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "barren_io.hpp"

#include <lib/identifier/id_name.hpp>

#include <ipc.hpp>
#include <messages.hpp>

using namespace pf;

namespace mind {
    
    ptr<identifier> g_barren_provider = new id_name(PLUGIN_BARREN_CACHE);
    
    ptr<barren> load_barren(long id) {
        ptr<barren> barren;
        ptr<serializable> rsp;
        rsp = call_plugin(g_barren_provider, M_LOAD_CACHE_BARREN, id);
        if (rsp != nullptr) {
            rsp >> barren;
        }
        return barren;
    }
    
    void save_barren(ptr<barren> obj) {
        send_to(g_barren_provider, M_SAVE_CACHE_BARREN, obj);
    }
    
}
