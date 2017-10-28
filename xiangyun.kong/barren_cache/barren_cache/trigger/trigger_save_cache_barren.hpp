//
//  trigger_on_put_barren.h
//  barren_cache
//
//  Created by 孔祥云 on 1/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_on_put_barren_h
#define trigger_on_put_barren_h

#include <barren_cache/barren_cache.hpp>

#include <plugin/trigger/trigger.hpp>

using namespace pf;

namespace mind {
    
    class save_cache_barren : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_SAVE_CACHE_BARREN);
        
    public:
        virtual void happen(ptr<plugin> plugin,ptr<event> event) override {
            ptr<barren_cache> owner = plugin;
            ptr<serializable> data = event->param();
            ptr<barren> barren;
            data >> barren;
            owner->save_barren(barren);
        }
        
    };
    
}

#endif /* trigger_on_put_barren_h */
