//
//  exe_on_put_barren.h
//  barren_cache
//
//  Created by 孔祥云 on 1/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_on_put_barren_h
#define exe_on_put_barren_h

#include <barren_cache/barren_cache.hpp>

using namespace pf;

namespace mind {
    
    class save_cache_barren : public executor {
    public:
        DECLARE_TYPE(executor, EXE_SAVE_CACHE_BARREN);
        
    public:
        virtual ptr<response> run(ptr<plugin> plugin,ptr<event> event) override {
            ptr<barren_cache> owner = plugin;
            ptr<serializable> data = event->param();
            ptr<barren> barren;
            data >> barren;
            owner->save_barren(barren);

            return nullptr;
        }
        
    };
    
}

#endif /* exe_on_put_barren_h */
