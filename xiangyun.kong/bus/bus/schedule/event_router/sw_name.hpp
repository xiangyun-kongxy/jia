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
        virtual void schedule(ptr<object> obj) override {
            ptr<event> evt = obj;
            ptr<cqueue<ptr<object>>> pool;
            pool = m_pools[evt->destination()->name()];
            if (pool != nullptr) {
                pool->push(obj);
            }
        }
        
        virtual void update_plugins() override {
            plugin_manager* pm = plugin_manager::instance();
            
            list<ptr<plugin>> pls = pm->get_all_plugin();
            m_pools.clear();
            for (ptr<plugin> pl : pls) {
                if (!pl->is_kind_of(PLUGIN_BUS) &&
                    !pl->is_kind_of(PLUGIN_PS)) {
                    m_pools[pl->name()] = pl->tasks();
                }
            }
            
        }
        
    private:
        map<string, ptr<cqueue<ptr<object>>>> m_pools;
    };
    
}

#endif /* sw_name_h */
