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

#include <iostream>

#include <log.hpp>

using namespace std;

namespace pf {
    
    class on_response : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_ON_RESPONSE);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<bus> bus = owner;
            ptr<serializable> data = evt->param();
            ptr<response> rsp;
            data >> rsp;

            logs::get_logger("bus")->info(evt->deliver()->name() + " response " +
                                          rsp->org_task()->caller()->name() +
                                          " " + rsp->org_task()->name());
            
            bus->set_object(rsp);
        }

    };
    
}

#endif /* trigger_on_response_h */
