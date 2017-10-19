/**
 * copyright @2016. all rights reserved.
 *
 * @since:  11:01 PM 8/10/16
 * @author: xiangyun kong
 *
 * description:
 *
 */

#ifndef PLUGIN_TRG_ON_ROUTING_EVENT_H
#define PLUGIN_TRG_ON_ROUTING_EVENT_H

#include <plugin/trigger/trigger.h>
#include <plugin/event/event.h>
#include <plugin/task/task.h>

#include <plugin/manager/plugin_manager.hpp>

#include <iostream>

using namespace std;

namespace pf {
    
    class on_route : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_ON_ROUTE);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<serializable> data = evt->param();
            ptr<identifier> dst = nullptr;


            ptr<object> msg;
            data >> msg;
            if(msg->is_kind_of(OBJ_EVENT)) {
                dst = ((ptr<event>)msg)->destination();

                if (((ptr<event>)msg)->deliver() != nullptr) {
                    cout << ((ptr<event>)msg)->deliver()->name() <<
                    " -> " << ((ptr<event>)msg)->name() << endl;
                }
            } else if(msg->is_kind_of(OBJ_TASK)) {
                dst = ((ptr<task>)msg)->processor();

                if (((ptr<task>)msg)->caller() != nullptr) {
                    cout << ((ptr<task>)msg)->caller()->name() <<
                    " -> " << ((ptr<task>)msg)->name() << endl;
                }
            }
            
            if(dst != nullptr) {
                const plugin_info* pi;
                pi = plugin_manager::instance()->find_plugin(dst);
                if (pi != nullptr && pi->is_active) {
                    pi->threads.front()->pool()->push(msg);
                }
            }
        }
        
    };
    
}

#endif //PLUGIN_TRG_ON_ROUTING_EVENT_H
