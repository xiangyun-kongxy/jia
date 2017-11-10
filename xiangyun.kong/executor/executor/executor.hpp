/*
 *  executor.hpp
 *  executor
 *
 *  Created by xiangyun.kong on 10/7/17.
 *  Copyright © 2017 xiangyun.kong. All rights reserved.
 *
 */

#ifndef executor_
#define executor_

#include <plugin/plugin/plugin.hpp>
#include <barren/barren.hpp>

#include <messages.hpp>

using namespace pf;

namespace mind {

    typedef ptr<barren> (*bfunction)(const deque<ptr<barren>>&);
    
    class barren_executor : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_BARREN_EXECUTOR);
        
        IMPL_BEGIN
        IMPL_F(T_NONE, M_EXECUTE_BARREN)
        IMPL_F(T_NONE, M_NEW_BARREN_FUNCTION)
        IMPL_END
        
    public:
        barren_executor();
        
    public:
        void exe_func(ptr<barren>);
        void new_barren_function(long, bfunction);

    };
}

#endif
