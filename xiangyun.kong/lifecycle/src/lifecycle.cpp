//
//  lifecycle.cpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include "lifecycle.hpp"
#include "executor/exe_load_plugin.h"
#include "lifecycle_function.h"

namespace pf{
    
    lifecycle::lifecycle() {
        m_task_processor[F_LOAD_PLUGIN] = new exe_load_plugin();
    }
    
    string lifecycle::type() const {
        return "lifecycle";
    }
    
    bool lifecycle::is_kind_of(const string &type_name) const {
        return type_name == "lifecycle" || plugin::is_kind_of(type_name);
    }
}
