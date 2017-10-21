//
//  trigger_stop_framework.hpp
//  lifecycle
//
//  Created by 孔祥云 on 10/21/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef trigger_stop_framework_h
#define trigger_stop_framework_h

#include <lib/identifier/id_name.h>

#include <plugin/trigger/trigger.h>
#include <plugin/manager/plugin_manager.hpp>
#include <plugin/manager/dependence_manager.hpp>

#include <common/identifier/id_simple_event.hpp>

#include <names.h>
#include <events.h>
#include <ipc.hpp>

namespace pf {
    
    class stop_framework : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_STOP_FRAMEWORK);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<lifecycle> lifecycle = owner;
            
            plugin_manager* pm = plugin_manager::instance();
            dependence_manager* dm = dependence_manager::instance();
            list<plugin_info> pis;
            do {
                list<plugin_info*> pis = pm->get_all_plugin();
                for (plugin_info* pi : pis) {
                    
                    if (pi->pl->name() != PLUGIN_LIFECYCLE &&
                        pi->pl->name() != PLUGIN_BUS &&
                        !dm->is_depended(pi->pl)) {
                        send_to(new id_name(PLUGIN_LIFECYCLE), EVT_UNLOAD_PLUGIN,
                                new id_name(pi->pl->name()));
                        wait_event(new id_simple_event(EVT_PLUGIN_UNLOADED));
                    }
                }
                sleep(1);
            } while (pis.size() > 2);
        }
        
    };
    
}

#endif /* trigger_stop_framework_h */
