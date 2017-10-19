//
//  trigger_new_compound_function.hpp
//  executor
//
//  Created by xiangyun.kong on 10/7/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef trigger_new_compound_function_h
#define trigger_new_compound_function_h

#include <plugin/trigger/trigger.h>

#include <executor/executor.hpp>

using namespace pf;

namespace mind {

    class new_compound_function : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_NEW_COMPOUND_FUNCTION);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<barren_executor> executor = owner;
            ptr<serializable> data = evt->param();
            long instruction;
            list<long> body;
            data >> instruction >> body;
            executor->new_compound_function(instruction, body);
        }

    };
}

#endif /* trigger_new_compound_function_h */
