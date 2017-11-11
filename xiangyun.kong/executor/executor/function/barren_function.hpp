//
//  barren_function.hpp
//  executor
//
//  Created by 孔祥云 on 11/11/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef barren_function_h
#define barren_function_h

#include <barren/barren.hpp>

#include <executor/executor.hpp>

namespace mind {
    
    class barren_function : public barren {
    public:
        bool is_function() const;
        
        bfunction get_raw_function() const;
        
    };
    
}

#endif /* barren_function_h */
