//
//  trigger_on_save_barren.h
//  memory
//
//  Created by 孔祥云 on 1/7/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_on_save_barren_h
#define trigger_on_save_barren_h

#include <memory/memory.hpp>

#include <plugin/trigger/trigger.hpp>

#include <class_names.hpp>

using namespace pf;

namespace mind {
    
    class save_barren : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_SAVE_BARREN);
        
    public:
        virtual void happen(ptr<plugin> plugin,ptr<event> event) override {
            ptr<memory> owner = plugin;
            ptr<serializable> data = event->param();
            ptr<barren> barren;
            data >> barren;
            owner->write(barren);
        }
        
    };
    
}

#endif /* trigger_on_save_barren_h */
