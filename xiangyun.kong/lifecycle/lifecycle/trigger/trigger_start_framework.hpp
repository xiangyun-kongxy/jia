//
//  trigger_start_framework.hpp
//  lifecycle
//
//  Created by xiangyun.kong on 10/16/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_start_framework_h
#define trigger_start_framework_h


#include <lib/identifier/id_name.h>

#include <plugin/trigger/trigger.h>
#include <plugin/plugin/config.hpp>

#include <lifecycle/load/loader.hpp>

#include <names.h>
#include <events.h>
#include <ipc.hpp>

namespace pf {

    class start_framework : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_START_FRAMEWORK);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<lifecycle> lifecycle = owner;
            ptr<serializable> data = evt->param();
            string path;
            data >> path;

            char* buf;
            list<config*> confs = loader::read_config_file(path, buf);
            lifecycle->set_config(buf, confs);
            
            list<config*>::const_iterator i;
            for(i = confs.begin(); i != confs.end(); ++i) {
                send_to(new id_name(PLUGIN_LIFECYCLE), EVT_LOAD_PLUGIN, *i);
            }
        }

    };
    
}


#endif /* trigger_start_framework_h */
