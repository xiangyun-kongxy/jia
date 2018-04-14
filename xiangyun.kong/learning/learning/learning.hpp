/*
 *  learning.hpp
 *  learning
 *
 *  Created by 孔祥云 on 3/24/18.
 *  Copyright © 2018 孔祥云. All rights reserved.
 *
 */

#ifndef learning_
#define learning_

#include <plugin/plugin/plugin.hpp>

using namespace pf;
using namespace kxy;

namespace mind {
    
    class learning : public plugin
    {
    public:
        DECLARE_TYPE(plugin, PLUGIN_LEARNING);
        
        IMPL_BEGIN
        IMPL_END
        
    public:
        learning();
        
        
    };

}

#endif
