/*
 *  heartbeat.cpp
 *  heartbeat
 *
 *  Created by 孔祥云 on 11/2/17.
 *  Copyright © 2017 孔祥云. All rights reserved.
 *
 */

#include "heartbeat.hpp"

#include <ipc.hpp>

#include <heartbeat/executors/exe_register_timer.hpp>
#include <heartbeat/executors/exe_unregister_timer.hpp>

namespace pf {
    
    heartbeat::heartbeat() {
        m_executors[M_REGISTER_TIMER] = new class register_timer;
        m_executors[M_UNREGISTER_TIMER] = new class unregister_timer;
    }
    
    void heartbeat::register_timer(ptr<identifier> who, long interval) {
        if (interval > 0) {
            m_timers[who] = pair<long,long>(time(nullptr)+interval, interval);
            
        }
    }
    
    void heartbeat::unregister_timer(ptr<object> who, long interval) {
        map<ptr<identifier>, pair<long, long>>::iterator i;
        for (i = m_timers.begin(); i != m_timers.end(); ++i) {
            if (i->first->match(who) && i->second.second == interval) {
                m_timers.erase(i);
                break;
            }
        }
    }
    
    void heartbeat::ontime(long cur) {
        map<ptr<identifier>, pair<long, long>>::iterator i;
        for (i = m_timers.begin(); i != m_timers.end(); ++i) {
            if (i->second.first == cur) {
                i->second.first += i->second.second;
                send_to(i->first, M_ON_TIMER);
            }
        }
    }
    
    extern "C" plugin* init_heartbeat(void*) {
        return new heartbeat;
    }
}

