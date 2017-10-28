//
//  trigger_start_framework.hpp
//  lifecycle
//
//  Created by xiangyun.kong on 10/16/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_start_framework_h
#define trigger_start_framework_h


#include <lib/identifier/id_name.hpp>

#include <plugin/trigger/trigger.hpp>
#include <plugin/plugin/plugin_config.hpp>

#include <lifecycle/load/loader.hpp>

#include <class_names.hpp>
#include <messages.hpp>
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
            list<plugin_config*> confs;
            confs = plugin_loader::read_config_file(path, buf);
            lifecycle->set_config(buf, confs);
            
            for(plugin_config* conf : confs) {
                send_to(new id_name(PLUGIN_LIFECYCLE), M_LOAD_PLUGIN, conf);
            }
        }

    };
    
}


#endif /* trigger_start_framework_h */
