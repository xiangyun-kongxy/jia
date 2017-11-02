/*
 *  heartbeat.hpp
 *  heartbeat
 *
 *  Created by 孔祥云 on 11/2/17.
 *  Copyright © 2017 孔祥云. All rights reserved.
 *
 */

#ifndef heartbeat_
#define heartbeat_

#include <plugin/plugin/plugin.hpp>
#include <messages.hpp>

namespace pf {
    
    class heartbeat : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_HEARTBEAT);
        
        IMPL_BEGIN
        IMPL_F(T_NONE, M_REGISTER_TIMER, T_INT);
        IMPL_F(T_NONE, M_UNREGISTER_TIMER, T_INT);
        IMPL_END
        
    public:
        heartbeat();
        
    public:
        void register_timer(ptr<identifier> who, long interval);
        
        void unregister_timer(ptr<object> who, long interval);
        
        void ontime(long cur);
        
    private:
        
        map<ptr<identifier>, pair<long,long>> m_timers;
    };
    
}

#endif
