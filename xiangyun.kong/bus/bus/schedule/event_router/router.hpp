//
//  router.hpp
//  bus
//
//  Created by 孔祥云 on 10/25/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef router_h
#define router_h

#include <stdio.h>

#include <bus/schedule/scheduler.hpp>

#include "sw_broadcast.hpp"
#include "sw_name.hpp"
#include "sw_sequence.hpp"

namespace pf {
    
    class router : public scheduler {
    public:
        router() {
            m_default_forward = new sw_sequence;
            m_forward_switchers[ID_ANY] = new sw_broadcast;
            m_forward_switchers[ID_NAME] = new sw_name;
        }

        virtual ~router() {
            delete m_default_forward;
            map<string, switcher*>::iterator i;
            for (i = m_forward_switchers.begin();
                 i != m_forward_switchers.end();
                 ++i) {
                delete i->second;
            }
        }
        
    public:
        virtual void schedule(ptr<object> obj) override {
            ptr<event> evt = obj;
            switcher* sw = m_forward_switchers[evt->destination()->type()];
            if (sw == nullptr) {
                sw = m_default_forward;
            }
            sw->schedule(obj);
        }
        
    public:
        virtual void update_plugins() {
            m_default_forward->update_plugins();
            
            map<string, switcher*>::iterator i;
            for (i = m_forward_switchers.begin();
                 i != m_forward_switchers.end();
                 ++i) {
                i->second->update_plugins();
            }
        }
        
    public:
        map<string, switcher*> m_forward_switchers;
        switcher* m_default_forward;
    };
}



#endif /* router_h */
