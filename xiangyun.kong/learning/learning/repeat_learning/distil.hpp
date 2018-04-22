//
//  distil.hpp
//  learning
//
//  Created by 孔祥云 on 4/22/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef distil_h
#define distil_h

#include "book.hpp"

using namespace kxy;

namespace mind {
    
    class distil : public reference {
    public:
        virtual ~distil() {}
        
    public:
        virtual ptr<book> perform(const vector<ptr<book>>& books) = 0;
    };
    
}

#endif /* distil_h */
