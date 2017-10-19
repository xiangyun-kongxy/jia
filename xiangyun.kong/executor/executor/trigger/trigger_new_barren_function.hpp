//
//  trigger_new_barren_fuction.hpp
//  executor
//
//  Created by xiangyun.kong on 10/7/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef trigger_new_barren_fuction_h
#define trigger_new_barren_fuction_h

#include <plugin/trigger/trigger.h>

#include <executor/executor.hpp>

using namespace pf;

namespace mind {

    class new_barren_function : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_NEW_BARREN_FUNCTION);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<serializable> data = evt->param();
            long instruction;
            barren_function func;
            data >> instruction >> (long&)func;
            ((ptr<barren_executor>)owner)->new_barren_function(instruction, func);
        }

    };
}

#endif /* trigger_new_barren_fuction_h */
