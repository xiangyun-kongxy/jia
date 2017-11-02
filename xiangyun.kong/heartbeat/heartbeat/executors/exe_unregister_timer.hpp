//
//  exe_unregister_timer.hpp
//  heartbeat
//
//  Created by 孔祥云 on 11/2/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_unregister_timer_h
#define exe_unregister_timer_h

#include <heartbeat/heartbeat.hpp>

#include <lib/identifier/id_name.hpp>

namespace pf {
    
    class unregister_timer : public executor {
    public:
        DECLARE_TYPE(executor, EXE_UNREGISTER_TIMER);
        
    public:
        ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<heartbeat> hb = owner;
            ptr<serializable> param = evt->param();
            long interval;
            param >> interval;
            hb->unregister_timer(new id_name(evt->deliver()->name()), interval);
            return nullptr;
        }
    };
}

#endif /* exe_unregister_timer_h */
