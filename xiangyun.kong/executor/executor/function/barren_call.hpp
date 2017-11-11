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

namespace mind {
    
    class barren_call : public barren {
    public:
        ptr<barren> call();
        bool is_call() const;
        
    private:
        ptr<barren> call(const deque<ptr<barren>>& params);
        
    };
}

#endif /* barren_call_hpp */
