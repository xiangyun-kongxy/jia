//
//  trigger_on_put_barren.h
//  barren_cache
//
//  Created by 孔祥云 on 1/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_on_put_barren_h
#define trigger_on_put_barren_h

#include <trigger/trigger.h>
#include "../barren_cache.hpp"
#include "../cache_function.h"

using namespace pf;

namespace mind {
    
    class trigger_on_put_barren : public trigger {
    public:
        virtual void occur(ptr<plugin> plugin,ptr<event> event) override {
            ptr<barren_cache> owner = plugin;
            ptr<serializable> data = event->param();
            ptr<barren> barren;
            data >> barren;
            owner->put_barren(barren);
        }
        
        virtual string type() const override {
            return "trigger_on_put_barren";
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "trigger_on_put_barren" || trigger::is_kind_of(type_name);
        }
    };
    
}

#endif /* trigger_on_put_barren_h */
