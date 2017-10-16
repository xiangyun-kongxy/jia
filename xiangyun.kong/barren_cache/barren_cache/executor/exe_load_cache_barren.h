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
        
        virtual string type() const override {
            return EXE_LOAD_CACHE_BARREN;
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == EXE_LOAD_CACHE_BARREN || object::is_kind_of(type_name);
        }
    };
    
}

#endif /* exe_on_get_barren_h */
