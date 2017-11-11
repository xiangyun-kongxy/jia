//
//  barren_function.cpp
//  executor
//
//  Created by 孔祥云 on 11/11/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#include "barren_function.hpp"

#include <predefined_barren.hpp>

namespace mind {
    
    map<long, bfunction> g_bfunctions;
    
    bool barren_function::is_function() const {
        return  size() > 2 &&
                (*(barren_function*)this)[1] == BARREN_DEFINE &&
                (*(barren_function*)this)[2] == BARREN_FUNCTION;
    }
    
    bfunction barren_function::get_raw_function() const {
        return g_bfunctions[id()];
    }
    
}
