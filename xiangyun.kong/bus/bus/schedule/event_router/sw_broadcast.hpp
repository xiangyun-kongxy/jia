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
        virtual void schedule(ptr<object> obj) override {
            if (m_pools.size() == 0) {
                update_plugins();
            }
            
            for (ptr<cqueue<ptr<object>>> pool : m_pools) {
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
                    m_pools.push_back(pl->tasks());
                }
            }
        }
        
    private:
        list<ptr<cqueue<ptr<object>>>> m_pools;
    };
    
}

#endif /* sw_broadcast_h */
