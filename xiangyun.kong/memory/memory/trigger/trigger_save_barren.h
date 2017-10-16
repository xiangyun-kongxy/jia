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

#include <plugin/trigger/trigger.h>

#include <names.h>

using namespace pf;

namespace mind {
    
    class save_barren : public trigger {
    public:
        virtual void occur(ptr<plugin> plugin,ptr<event> event) override {
            ptr<memory> owner = plugin;
            ptr<serializable> data = event->param();
            ptr<barren> barren;
            data >> barren;
            owner->write(barren);
        }
        
        virtual string type() const override {
            return TRIGGER_SAVE_BARREN;
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == TRIGGER_SAVE_BARREN || object::is_kind_of(type_name);
        }
    };
    
}

#endif /* trigger_on_save_barren_h */
