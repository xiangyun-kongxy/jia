//
//  barren_set.hpp
//  barren
//
//  Created by 孔祥云 on 10/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef barren_set_hpp
#define barren_set_hpp

#include <stdio.h>
#include "../barren.hpp"

namespace mind {
    
    class barren_set : public barren {
    public:
        void add(long id);
        void remove(long id);
        bool contain(long id) const;
    };
}

#endif /* barren_set_hpp */
