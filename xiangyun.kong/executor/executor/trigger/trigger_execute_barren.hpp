//
//  trigger_execute_barren.hpp
//  executor
//
//  Created by xiangyun.kong on 10/7/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef trigger_execute_barren_h
#define trigger_execute_barren_h

#include <trigger/trigger.h>
#include <names.h>

using namespace pf;

namespace mind {

    class execute_barren : public trigger {
    public:
        virtual void occur(ptr<plugin> owner, ptr<event> evt) override {
            ptr<serializable> data = evt->param();
            ptr<barren> br;
            data >> br;
            ((ptr<barren_executor>)owner)->exe_func(br);
        }

        virtual string type() const override {
            return TRIGGER_EXECUTE_BARREN;
        }

        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == TRIGGER_EXECUTE_BARREN || trigger::is_kind_of(type_name);
        }
    };
}

#endif /* trigger_execute_barren_h */
