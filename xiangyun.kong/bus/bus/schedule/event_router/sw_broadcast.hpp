//
//  sw_broadcast.hpp
//  bus
//
//  Created by 孔祥云 on 10/25/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef sw_broadcast_h
#define sw_broadcast_h

#include "switcher.hpp"
#include <plugin/manager/plugin_manager.hpp>

namespace pf {
    
    class sw_broadcast : public switcher {
    public:
        sw_broadcast() {
            update_plugins();
        }
        
    public:
        virtual void schedule(ptr<event> evt) override {
            for (ptr<cqueue<ptr<object>>> pool : m_pools) {
                pool->push(evt);
            }
        }
        
        virtual void update_plugins() override {
            plugin_manager* pm = plugin_manager::instance();
            
            pm->lock();
            
            list<plugin_info*> pi = pm->get_all_plugin();
            m_pools.clear();
            for (plugin_info* i : pi) {
                if (!i->pl->is_kind_of(PLUGIN_BUS)) {
                    m_pools.insert(i->threads->front()->pool());
                }
            }
            
            pm->unlock();
        }
        
    private:
        set<ptr<cqueue<ptr<object>>>> m_pools;
    };
    
}

#endif /* sw_broadcast_h */
