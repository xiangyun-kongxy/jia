//
//  trigger_load_plugin.hpp
//  lifecycle
//
//  Created by xiangyun.kong on 10/16/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_load_plugin_h
#define trigger_load_plugin_h

#include <lib/identifier/id_name.h>

#include <plugin/trigger/trigger.h>
#include <plugin/plugin/config.hpp>

#include <lifecycle/load/loader.hpp>

#include <names.h>
#include <events.h>
#include <ipc.hpp>


namespace pf {

    class load_plugin : public trigger {
    public:

        virtual void occur(ptr<plugin> owner, ptr<event> evt) override {
            ptr<lifecycle> lifecycle = owner;
            ptr<serializable> data = evt->param();
            config* conf = nullptr;
            data >> conf;

            if (conf != nullptr) {
                ptr<plugin> plugin = loader::load_plugin(conf);

                /*
                while(!lifecycle->is_satisfied(plugin)) {

                }
                 */
            }

        }

        virtual string type() const override {
            return TRIGGER_START_FRAMEWORK;
        }

        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == TRIGGER_START_FRAMEWORK
                    || object::is_kind_of(type_name);
        }
    };

}


#endif /* trigger_load_plugin_h */
