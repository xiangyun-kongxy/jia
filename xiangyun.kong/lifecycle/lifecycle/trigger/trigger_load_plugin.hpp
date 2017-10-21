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

#include <log.hpp>

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
                logs::get_logger("info")->info(conf->get_name() + " is loading...");
                
                broadcast(EVT_PLUGIN_LOADING, conf->get_name());
                ptr<plugin> plugin = loader::load_plugin(conf);
                broadcast(EVT_PLUGIN_LOADED, conf->get_name());

                broadcast(EVT_PLUGIN_INSTALLING, conf->get_name());
                plugin_manager::instance()->add_plugin(plugin);

                dependence_manager* dm = dependence_manager::instance();
                plugin_manager* pm = plugin_manager::instance();
                do {
                    if (dm->is_depend_ready(plugin)) {
                        plugin->init();
                        broadcast(EVT_PLUGIN_INSTALLED, conf->get_name());
                        pm->active_plugin(new id_name(plugin->name()));
                        broadcast(EVT_PLUGIN_RUNNING, conf->get_name());
                        break;
                    } else {
                        wait_event(new id_simple_event(EVT_PLUGIN_RUNNING));
                    }
                } while (true);
                
                logs::get_logger("info")->info(conf->get_name() + " is loaded");
            }

        }

    };

}


#endif /* trigger_load_plugin_h */
