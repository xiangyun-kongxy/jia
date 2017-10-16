//
//  trigger_new_barren_fuction.hpp
//  executor
//
//  Created by xiangyun.kong on 10/7/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef trigger_new_barren_fuction_h
#define trigger_new_barren_fuction_h

#include <trigger/trigger.h>
#include "../executor.hpp"

using namespace pf;

namespace mind {

    class new_barren_function : public trigger {
    public:
        virtual void occur(ptr<plugin> owner, ptr<event> evt) override {
            ptr<serializable> data = evt->param();
            long instruction;
            barren_function func;
            data >> instruction >> (long&)func;
            ((ptr<barren_executor>)owner)->new_barren_function(instruction, func);
        }

        virtual string type() const override {
            return TRIGGER_NEW_BARREN_FUNCTION;
        }

        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == TRIGGER_NEW_BARREN_FUNCTION
            || trigger::is_kind_of(type_name);
        }
    };
}

#endif /* trigger_new_barren_fuction_h */