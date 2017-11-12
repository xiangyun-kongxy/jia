//
//  barren_call.hpp
//  executor
//
//  Created by 孔祥云 on 11/9/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef barren_call_hpp
#define barren_call_hpp

#include <barren/barren.hpp>
#include <executor/executor.hpp>
#include <executor/function/barren_function.hpp>

namespace mind {
    
    class barren_call : public barren {
    public:
        ptr<barren> call();
        bool is_call() const;
        
    private:
        ptr<barren> _call(const deque<ptr<barren>>& params);
        deque<ptr<barren>> _init_param(const deque<ptr<barren>>& gp);
        ptr<barren_function> _get_function(const deque<ptr<barren>>&);
    };
}

#endif /* barren_call_hpp */
