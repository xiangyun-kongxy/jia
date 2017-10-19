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
#include <plugin/manager/plugin_manager.hpp>
#include <plugin/manager/dependence_manager.hpp>

#include <lifecycle/load/loader.hpp>

#include <common/identifier/id_simple_event.hpp>

#include <names.h>
#include <events.h>
#include <ipc.hpp>


namespace pf {

    class load_plugin : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_LOAD_PLUGIN);

    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<lifecycle> lifecycle = owner;
            ptr<serializable> data = evt->param();
            config* conf = nullptr;
            data >> conf;

            if (conf != nullptr) {
                ptr<serializable> param;

                param = new serializable;
                param << conf->get_name();
                send_message(new simple_event(EVT_PLUGIN_LOADING, param));
                
                ptr<plugin> plugin = loader::load_plugin(conf);

                param = new serializable;
                param << conf->get_name();
                send_message(new simple_event(EVT_PLUGIN_LOADED, param));

                param = new serializable;
                param << conf->get_name();
                send_message(new simple_event(EVT_PLUGIN_INSTALLING, param));

                plugin_manager::instance()->add_plugin(plugin);

                dependence_manager* dm = dependence_manager::instance();
                plugin_manager* pm = plugin_manager::instance();
                do {
                    if (dm->is_depend_ready(plugin)) {
                        param = new serializable;
                        param << conf->get_name();
                        send_message(new simple_event(EVT_PLUGIN_INSTALLED,
                                                      param));

                        pm->active_plugin(new id_name(plugin->name()));

                        param = new serializable;
                        param << conf->get_name();
                        send_message(new simple_event(EVT_PLUGIN_RUNNING,
                                                      param));
                        break;
                    } else {
                        wait_event(new id_simple_event(EVT_PLUGIN_RUNNING));
                    }
                } while (true);
            }

        }

    };

}


#endif /* trigger_load_plugin_h */
