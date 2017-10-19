//
//  exe_on_get_barren.h
//  barren_cache
//
//  Created by 孔祥云 on 1/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_on_get_barren_h
#define exe_on_get_barren_h

#include <barren_cache/barren_cache.hpp>

#include <plugin/executor/executor.h>
#include <plugin/response/simple_response.h>

#include <errors.h>

using namespace pf;

namespace mind {
    
    class load_cache_barren : public executor {
    public:
        DECLARE_TYPE(executor, EXE_LOAD_CACHE_BARREN);

    public:
        virtual ptr<response> run(ptr<plugin> plugin, ptr<task> tsk) override {
            ptr<barren_cache> owner = plugin;
            ptr<serializable> data = tsk->param();
            long id = 0;
            data >> id;
            ptr<barren> barren = owner->load_barren(id);
            if(barren != nullptr) {
                data << barren;
                return new simple_response(tsk, EC_OK, EM_OK, data);
            } else {
                return new simple_response(tsk, EC_NOT_EXIST, EM_NOT_EXIST);
            }
        }
        
    };
    
}

#endif /* exe_on_get_barren_h */
