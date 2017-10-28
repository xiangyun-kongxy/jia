//
//  trigger_load_plugin.hpp
//  lifecycle
//
//  Created by xiangyun.kong on 10/16/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_load_plugin_h
#define trigger_load_plugin_h

#include <lib/identifier/id_name.hpp>

#include <plugin/trigger/trigger.hpp>
#include <plugin/plugin/plugin_config.hpp>
#include <plugin/manager/plugin_manager.hpp>
#include <plugin/manager/dependence_manager.hpp>

#include <lifecycle/load/loader.hpp>

#include <common/identifier/id_simple_event.hpp>

#include <class_names.hpp>
#include <messages.hpp>
#include <ipc.hpp>

#include <log.hpp>

#include <iostream>

using namespace std;

namespace pf {

    class load_plugin : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_LOAD_PLUGIN);

    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<lifecycle> lifecycle = owner;
            ptr<serializable> data = evt->param();
            plugin_config* conf = nullptr;
            data >> conf;

            if (conf != nullptr) {
                info_log("info", conf->get_name() + " is loading...");
                
                broadcast(M_PLUGIN_LOADING, conf->get_name());
                ptr<plugin> plugin = plugin_loader::load_plugin(conf);
                if (plugin == nullptr) {
                    error_log("error", conf->get_name() + " failed to load.");
                    return;
                }
                broadcast(M_PLUGIN_LOADED, conf->get_name());

                broadcast(M_PLUGIN_INSTALLING, conf->get_name());
                plugin->init();

                dependence_manager* dm = dependence_manager::instance();
                do {
                    if (dm->is_depend_ready(plugin)) {
                        broadcast(M_PLUGIN_INSTALLED, conf->get_name());
                        plugin->resume();
                        broadcast(M_PLUGIN_RUNNING, conf->get_name());
                        break;
                    } else {
                        wait_object(new id_simple_event(M_PLUGIN_RUNNING));
                    }
                } while (true);
                
                info_log("info", conf->get_name() + " is loaded");
            } else {
                cout << "error" << endl;
            }

        }

    };

}


#endif /* trigger_load_plugin_h */
