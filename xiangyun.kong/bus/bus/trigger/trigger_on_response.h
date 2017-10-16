//
//  trigger_on_response.h
//  plugin-framework
//
//  Created by 孔祥云 on 10/5/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef trigger_on_response_h
#define trigger_on_response_h

#include <plugin/trigger/trigger.h>
#include <plugin/plugin/plugin.h>
#include <plugin/event/simple_event.h>

namespace pf {
    
    class on_response : public trigger {
    public:
        virtual void occur(ptr<plugin> owner, ptr<event> evt) override {
            ptr<bus> bus = owner;
            ptr<serializable> data = evt->param();
            ptr<task> tsk;
            ptr<response> rsp;
            data >> tsk >> rsp;
            bus->set_object(rsp);
        }
        
        virtual string type() const override {
            return TRIGGER_ON_RESPONSE;
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == TRIGGER_ON_RESPONSE || trigger::is_kind_of(type_name);
        }
    };
    
}

#endif /* trigger_on_response_h */
