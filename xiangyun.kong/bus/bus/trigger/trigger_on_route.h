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

#include <bus/bus.h>

#include <log.hpp>

#include <iostream>

using namespace std;

namespace pf {
    
    class on_route : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_ON_ROUTE);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<bus> bus = owner;
            ptr<serializable> data = evt->param();
            ptr<identifier> dst = nullptr;


            ptr<object> msg;
            data >> msg;
            bus->set_object(msg);

            
            if(msg->is_kind_of(OBJ_EVENT)) {
                ptr<event> e = msg;
                dst = e->destination();
                
                logs::get_logger("bus")->info(e->deliver()->name() + " send to " +
                                              dst->name() + " " + e->name());
            } else if(msg->is_kind_of(OBJ_TASK)) {
                ptr<task> t = msg;
                dst = t->processor();
                logs::get_logger("bus")->info(t->caller()->name() + " send to " +
                                              dst->name() + " " + t->name());
            }
            
            
            const plugin_info* pi;
            pi = plugin_manager::instance()->find_plugin(dst);
            if (pi != nullptr && pi->is_active) {
                pi->threads->front()->pool()->push(msg);
            }
        }
        
    };
    
}

#endif //PLUGIN_TRG_ON_ROUTING_EVENT_H
