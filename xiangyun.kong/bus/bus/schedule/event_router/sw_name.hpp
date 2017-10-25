//
//  sw_name.hpp
//  bus
//
//  Created by 孔祥云 on 10/25/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef sw_name_h
#define sw_name_h

#include "switcher.hpp"
#include <plugin/manager/plugin_manager.hpp>

namespace pf {
    
    class sw_name : public switcher {
    public:
        sw_name() {
            update_plugins();
        }
        
    public:
        virtual void schedule(ptr<event> evt) override {
            ptr<cqueue<ptr<object>>> pool;
            pool = m_pools[evt->destination()->name()];
            if (pool != nullptr) {
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
                    m_pools[i->pl->name()] = i->threads->front()->pool();
                }
            }
            
            pm->unlock();
        }
        
    private:
        map<string, ptr<cqueue<ptr<object>>>> m_pools;
    };
    
}

#endif /* sw_name_h */
