//
//  barren_io.hpp
//  barren
//
//  Created by 孔祥云 on 1/13/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef barren_io_hpp
#define barren_io_hpp

#include <barren/barren.hpp>

namespace mind {
    
    ptr<barren> load_barren(long id);
    void save_barren(ptr<barren> obj);
    
}

#endif /* barren_io_hpp */
