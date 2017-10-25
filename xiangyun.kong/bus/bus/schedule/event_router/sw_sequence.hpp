//
//  sw_sequence.hpp
//  bus
//
//  Created by 孔祥云 on 10/25/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef sw_sequence_h
#define sw_sequence_h

#include "switcher.hpp"
#include <plugin/manager/plugin_manager.hpp>

namespace pf {
    
    class sw_sequence : public switcher {
    public:
        sw_sequence() {
            update_plugins();
        }
        
    public:
        virtual void schedule(ptr<event> evt) override {
            map<ptr<plugin>, ptr<cqueue<ptr<object>>>>::iterator i;
            for (i = m_pools.begin(); i != m_pools.end(); ++i) {
                if (evt->destination()->match(i->first)) {
                    i->second->push(evt);
                }
            }
        }
        
        virtual void update_plugins() override {
            plugin_manager* pm = plugin_manager::instance();
            
            pm->lock();
            
            list<plugin_info*> pi = pm->get_all_plugin();
            m_pools.clear();
            for (plugin_info* i : pi) {
                if (!i->pl->is_kind_of(PLUGIN_BUS)) {
                    m_pools[i->pl] = i->threads->front()->pool();
                }
            }
            
            pm->unlock();
        }
        
    private:
        map<ptr<plugin>, ptr<cqueue<ptr<object>>>> m_pools;
    };
    
}

#endif /* sw_sequence_h */
