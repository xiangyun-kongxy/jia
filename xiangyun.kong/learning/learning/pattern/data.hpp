//
//  data.hpp
//  learning
//
//  Created by 孔祥云 on 4/14/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef data_hpp
#define data_hpp

#include <lib/object/reference.hpp>
#include <lib/object/ptr.hpp>

#include <barren/barren.hpp>

using namespace kxy;

namespace mind {
        
        class data : public reference {
        public:
                virtual ~data();
        public:
                virtual ptr<barren> operator [] (int pos) = 0;
                virtual long size() = 0;
                virtual long version() = 0;
        };
        
}

#endif /* data_hpp */
