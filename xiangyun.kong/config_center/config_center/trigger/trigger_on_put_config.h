//
//  trigger_on_put_config.h
//  config_center
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_on_put_config_h
#define trigger_on_put_config_h

#include <trigger/trigger.h>
#include "../config_center.hpp"
#include "../config_functions.h"

using namespace pf;

namespace kxy {
    
    class trigger_on_put_config : public trigger {
    public:
        virtual void occur(ptr<plugin> plugin,ptr<event> event) override {
            ptr<config_center> owner = plugin;
            ptr<serializable> data = event->param();
            string key;
            string config;
            data >> key >> config;
            owner->put(key, config);
        }
        
        virtual string type() const override {
            return "trigger_on_put_config";
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "trigger_on_put_config" || trigger::is_kind_of(type_name);
        }
    };
    
}

#endif /* trigger_on_put_config_h */
