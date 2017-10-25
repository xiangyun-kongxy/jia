//
//  exe_on_load_barren.h
//  memory
//
//  Created by 孔祥云 on 1/8/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_on_load_barren_h
#define exe_on_load_barren_h

#include <memory/memory.hpp>

#include <plugin/executor/executor.h>
#include <plugin/response/simple_response.h>

#include <errors.h>
#include <names.h>

using namespace pf;

namespace mind {
    
    class load_barren : public executor {
    public:
        DECLARE_TYPE(executor, EXE_LOAD_BARREN);
        
    public:
        virtual ptr<response> run(ptr<plugin> plugin, ptr<event> evt) override {
            ptr<memory> owner = plugin;
            ptr<serializable> data = evt->param();
            long id;
            data >> id;
            ptr<barren> barren = owner->read(id);
            if(barren != nullptr) {
                data << barren;
                return new simple_response(evt, EC_OK, EM_OK, data);
            } else {
                return new simple_response(evt, EC_NOT_EXIST, EM_NOT_EXIST);
            }
        }
        
    };
    
}

#endif /* exe_on_load_barren_h */
