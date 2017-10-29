//
//  exe_unload_plugin.hpp
//  lifecycle
//
//  Created by 孔祥云 on 10/21/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_unload_plugin_h
#define exe_unload_plugin_h

#include <lib/identifier/id_name.hpp>

#include <plugin/manager/plugin_manager.hpp>
#include <plugin/manager/dependence_manager.hpp>

#include <common/identifier/id_simple_event.hpp>

#include <class_names.hpp>
#include <messages.hpp>
#include <ipc.hpp>
#include <log.hpp>

using namespace kxy;

namespace pf {
    
    class unload_plugin : public executor {
    public:
        DECLARE_TYPE(executor, EXE_UNLOAD_PLUGIN);
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<lifecycle> lifecycle = owner;
            ptr<serializable> data = evt->param();
            ptr<identifier> id;
            data >> id;
            
            if (id != nullptr) {
                dependence_manager* dm = dependence_manager::instance();
                plugin_manager* pm = plugin_manager::instance();
                if (!dm->is_depended(id)) {
                    while (pm->has_task(id) ||
                           pm->has_task(new id_name(PLUGIN_BUS))) {
                        usleep(32000);
                    }
                    ptr<plugin> pl = pm->find_plugin(id);
                    if (pl != nullptr) {
                        info_log("info", id->name() + " is exiting...");
                        
                        broadcast(M_PLUGIN_UNINSTALLING, id->name());
                        pl->uninit();
                        broadcast(M_PLUGIN_UNINSTALLED, id->name());
                        broadcast(M_PLUGIN_UNLOADING, id->name());
                        pl = nullptr;
                        broadcast(M_PLUGIN_UNLOADED, id->name());
                        
                        info_log("info", id->name() + " is exited");
                    }
                }
            }
            
            return nullptr;
        }
        
    };
    
}

#endif /* exe_unload_plugin_h */
