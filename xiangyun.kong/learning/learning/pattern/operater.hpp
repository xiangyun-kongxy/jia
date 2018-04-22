//
//  operater.hpp
//  learning
//
//  Created by 孔祥云 on 4/14/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef operater_hpp
#define operater_hpp

#include "data.hpp"

using namespace kxy;

namespace mind {
        
        class operater : public reference {
        public:
                virtual ~operater();
                
        public:
                virtual ptr<data> compute(const vector<ptr<data>> opd) = 0;
        };
        
}

#endif /* operater_hpp */
