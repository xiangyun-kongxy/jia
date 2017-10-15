//
//  trigger_new_compound_function.hpp
//  executor
//
//  Created by xiangyun.kong on 10/7/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef trigger_new_compound_function_h
#define trigger_new_compound_function_h

#include <trigger/trigger.h>
#include "../executor.hpp"

using namespace pf;

namespace mind {

    class new_compound_function : public trigger {
    public:
        virtual void occur(ptr<plugin> owner, ptr<event> evt) override {
            ptr<serializable> data = evt->param();
            long instruction;
            list<long> body;
            data >> instruction >> body;
            ((ptr<barren_executor>)owner)->new_compound_function(instruction, body);
        }

        virtual string type() const override {
            return TRIGGER_NEW_COMPOUND_FUNCTION;
        }

        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == TRIGGER_NEW_COMPOUND_FUNCTION
            || trigger::is_kind_of(type_name);
        }
    };
}

#endif /* trigger_new_compound_function_h */
