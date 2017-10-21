//
//  trigger_unload_plugin.hpp
//  lifecycle
//
//  Created by 孔祥云 on 10/21/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_unload_plugin_h
#define trigger_unload_plugin_h

#include <lib/identifier/id_name.h>

#include <plugin/trigger/trigger.h>
#include <plugin/plugin/config.hpp>
#include <plugin/manager/plugin_manager.hpp>
#include <plugin/manager/dependence_manager.hpp>

#include <common/identifier/id_simple_event.hpp>

#include <names.h>
#include <events.h>
#include <ipc.hpp>
#include <log.hpp>

using namespace kxy;

namespace pf {
    
    class unload_plugin : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_UNLOAD_PLUGIN);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<lifecycle> lifecycle = owner;
            ptr<serializable> data = evt->param();
            ptr<identifier> id;
            data >> id;
            
            if (id != nullptr) {
                dependence_manager* dm = dependence_manager::instance();
                plugin_manager* pm = plugin_manager::instance();
                if (!dm->is_depended(id)) {
                    const plugin_info* pi = pm->find_plugin(id);
                    if (pi != nullptr) {
                        logs::get_logger("info")->info(id->name() + " is exiting...");
                        
                        broadcast(EVT_PLUGIN_UNINSTALLING, id->name());
                        pi->pl->uninit();
                        pm->suspend_plugin(id);
                        broadcast(EVT_PLUGIN_UNINSTALLED, id->name());
                        broadcast(EVT_PLUGIN_UNLOADING, id->name());
                        pm->rm_plugin(id);
                        broadcast(EVT_PLUGIN_UNLOADED, id->name());
                        
                        logs::get_logger("info")->info(id->name() + " is exited");
                    }
                }
            }
            
        }
        
    };
    
}

#endif /* trigger_unload_plugin_h */
