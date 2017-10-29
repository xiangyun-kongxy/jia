//
//  exe_on_save_barren.h
//  memory
//
//  Created by 孔祥云 on 1/7/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_on_save_barren_h
#define exe_on_save_barren_h

#include <memory/memory.hpp>

using namespace pf;

namespace mind {
    
    class save_barren : public executor {
    public:
        DECLARE_TYPE(executor, EXE_SAVE_BARREN);
        
    public:
        virtual ptr<response> run(ptr<plugin> plugin,ptr<event> event) override {
            ptr<memory> owner = plugin;
            ptr<serializable> data = event->param();
            ptr<barren> barren;
            data >> barren;
            owner->write(barren);

            return nullptr;
        }
        
    };
    
}

#endif /* exe_on_save_barren_h */
