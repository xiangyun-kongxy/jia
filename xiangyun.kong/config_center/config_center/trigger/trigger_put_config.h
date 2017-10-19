//
//  trigger_on_put_config.h
//  config_center
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_on_put_config_h
#define trigger_on_put_config_h

#include <plugin/trigger/trigger.h>

#include <config_center/config_center.hpp>

using namespace pf;

namespace kxy {
    
    class put_config : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_PUT_CONFIG);
        
    public:
        virtual void happen(ptr<plugin> plugin,ptr<event> event) override {
            ptr<config_center> owner = plugin;
            ptr<serializable> data = event->param();
            string key;
            string config;
            data >> key >> config;
            owner->put(key, config);
        }
        
    };
    
}

#endif /* trigger_on_put_config_h */
