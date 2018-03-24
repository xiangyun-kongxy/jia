/*
 *  gower.hpp
 *  gower
 *
 *  Created by 孔祥云 on 3/10/18.
 *  Copyright © 2018 孔祥云. All rights reserved.
 *
 */

#ifndef gower_
#define gower_

#include <plugin/plugin/plugin.hpp>
#include <plugin/function/function.hpp>

#include <lib/object/ptr.hpp>
#include <lib/object/type_info.hpp>

using namespace kxy;
using namespace pf;

namespace mind {
    
    class gower : public plugin
    {
    public:
        DECLARE_TYPE(plugin, PLUGIN_GOWER);
        
        IMPL_BEGIN
        IMPL_END
        
    public:
        gower();
    };
    
}

#endif
