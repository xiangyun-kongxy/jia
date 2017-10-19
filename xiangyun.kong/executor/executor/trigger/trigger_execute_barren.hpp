//
//  trigger_execute_barren.hpp
//  executor
//
//  Created by xiangyun.kong on 10/7/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef trigger_execute_barren_h
#define trigger_execute_barren_h

#include <plugin/trigger/trigger.h>

#include <names.h>

using namespace pf;

namespace mind {

    class execute_barren : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_EXECUTE_BARREN);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<serializable> data = evt->param();
            ptr<barren> br;
            data >> br;
            ((ptr<barren_executor>)owner)->exe_func(br);
        }

    };
}

#endif /* trigger_execute_barren_h */
