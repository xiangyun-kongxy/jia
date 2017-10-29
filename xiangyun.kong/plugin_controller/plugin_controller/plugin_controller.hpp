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

namespace pf {
    
    class plugin_controller : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_CONTROLLER);
        
    public:
        plugin_controller();
    };
    
}

#endif
