//
//  barren_io.cpp
//  barren
//
//  Created by 孔祥云 on 1/13/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "barren_io.hpp"
#include <barren_cache/cache_function.h>
#include <task/simple_task.h>
#include <event/simple_event.h>
#include <identifier/id_name.h>
#include <response/response.h>
#include <bus/ipc.hpp>

using namespace pf;

namespace mind {
    
    ptr<identifier> g_barren_provider = new id_name("barren_cache");
    
    ptr<barren> get_barren(long id) {
        ptr<serializable> rsp;
        rsp = call_plugin(g_barren_provider, F_ON_GET_BARREN, id);
        ptr<barren> barren;
        rsp >> barren;
        return barren;
    }
    
    void put_barren(ptr<barren> obj) {
        ptr<serializable> param;
        param << obj;
        ptr<event> evt = new simple_event(F_ON_PUT_BARREN, param, g_barren_provider);
        send_message(evt);
    }
    
}
