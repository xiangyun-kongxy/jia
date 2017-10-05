//
//  barren_io.hpp
//  barren
//
//  Created by 孔祥云 on 1/13/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef barren_io_hpp
#define barren_io_hpp

#include <string>
#include <object/ptr.h>
#include "../barren.hpp"

using namespace std;
using namespace kxy;

namespace mind {
    
    ptr<barren> get_barren(long id);
    void put_barren(ptr<barren> obj);
    
}

#endif /* barren_io_hpp */
