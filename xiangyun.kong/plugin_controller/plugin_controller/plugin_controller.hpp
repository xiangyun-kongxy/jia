/*
 *  plugin_controller.hpp
 *  plugin_controller
 *
 *  Created by 孔祥云 on 10/29/17.
 *  Copyright © 2017 孔祥云. All rights reserved.
 *
 */

#ifndef plugin_controller_
#define plugin_controller_

#include <plugin/plugin/plugin.hpp>

#include <messages.hpp>

namespace pf {
    
    class plugin_controller : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_CONTROLLER);
        
        IMPL_BEGIN
        IMPL_F(T_NONE, M_INC_THREAD, T_STR)
        IMPL_F(T_NONE, M_DEC_THREAD, T_STR)
        IMPL_F(T_INT, M_SHOW_TASK_COUNT, T_STR)
        IMPL_F(T_STR, M_SHOW_PLUGINS)
        IMPL_END
        
    public:
        plugin_controller();
    };
    
}

#endif
