//
//  exe_on_load_barren.h
//  memory
//
//  Created by 孔祥云 on 1/8/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_on_load_barren_h
#define exe_on_load_barren_h

#include <executor/executor.h>
#include <response/simple_response.h>
#include <constants.h>
#include "../memory.hpp"
#include "../memory_function.h"

using namespace pf;

namespace mind {
    
    class exe_on_load_barren : public executor {
    public:
        virtual ptr<response> run(ptr<plugin> plugin, ptr<task> task) override {
            ptr<memory> owner = plugin;
            ptr<serializable> data = task->param();
            string id;
            data >> id;
            ptr<barren> barren = owner->read(id);
            if(barren != nullptr) {
                data << barren;
                return new simple_response(EC_OK, EM_OK, data);
            } else {
                return new simple_response(EC_NOT_EXIST, EM_NOT_EXIST);
            }
        }
        
        virtual string type() const override {
            return "exe_on_load_barren";
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "exe_on_load_barren" || object::is_kind_of(type_name);
        }
    };
    
}

#endif /* exe_on_load_barren_h */
