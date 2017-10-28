//
//  trigger_stop_framework.hpp
//  lifecycle
//
//  Created by 孔祥云 on 10/21/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_stop_framework_h
#define trigger_stop_framework_h

#include <lib/identifier/id_name.hpp>

#include <plugin/trigger/trigger.hpp>
#include <plugin/manager/plugin_manager.hpp>
#include <plugin/manager/dependence_manager.hpp>

#include <common/identifier/id_simple_event.hpp>

#include <class_names.hpp>
#include <messages.hpp>
#include <ipc.hpp>

#include <unistd.h>

namespace pf {
    
    class stop_framework : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_STOP_FRAMEWORK);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<lifecycle> lifecycle = owner;
            
            set<string> exc_plugin;
            exc_plugin.insert(PLUGIN_BUS);
            exc_plugin.insert(PLUGIN_LIFECYCLE);

            plugin_manager* pm = plugin_manager::instance();
            dependence_manager* dm = dependence_manager::instance();
            list<ptr<plugin>> pls;
            do {
                pls = pm->get_all_plugin();
                for (ptr<plugin> pl : pls) {

                    if (exc_plugin.end() == exc_plugin.find(pl->name()) &&
                        !dm->is_depended(pl)) {
                        send_to(new id_name(PLUGIN_LIFECYCLE), M_UNLOAD_PLUGIN,
                                ptr<id_name>(new id_name(pl->name())));
                        exc_plugin.insert(pl->name());
                    }
                }
                sleep(1);
            } while (pls.size() > 2);
        }
        
    };
    
}

#endif /* trigger_stop_framework_h */
