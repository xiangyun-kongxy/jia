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

#include <trigger/trigger.h>
#include <event/event.h>
#include <task/task.h>
#include <manager/plugin_manager.hpp>

namespace pf {
    
    class trigger_on_routing_event : public trigger {
        
    public:
        virtual void occur(ptr<plugin> owner, ptr<event> evt) override {
            ptr<serializable> data = evt->param();
            ptr<identifier> dst = nullptr;
            
            ptr<object> msg;
            data >> msg;
            if(msg->is_kind_of("event")) {
                dst = ((ptr<event>)msg)->destination();
            } else if(msg->is_kind_of("task")) {
                dst = ((ptr<task>)msg)->processor();
            }
            
            if(dst != nullptr) {
                list<ptr<plugin_thread>> threads;
                list<ptr<plugin>> plugins;
                plugins = plugin_manager::instance()->find_plugin(dst);

                list<ptr<plugin>>::iterator i;
                for (i = plugins.begin(); i != plugins.end(); ++i) {
                    threads = plugin_manager::instance()->get_plugin_thread(*i);
                    if(threads.size() > 0) {
                        threads.front()->pool()->push(msg);
                    }
                }
            }
        }
        
    public:
        virtual string type() const override {
            return "trigger_on_routing_event";
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "trigger_on_routing_event" || trigger::is_kind_of(type_name);
        }
        
    };
    
}

#endif //PLUGIN_TRG_ON_ROUTING_EVENT_H
