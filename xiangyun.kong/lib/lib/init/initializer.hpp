//
//  initializer.hpp
//  lib
//
//  Created by 孔祥云 on 10/21/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef initializer_hpp
#define initializer_hpp

#include <string>

using namespace std;

namespace kxy {
    
    typedef void (*uninit_func)(void);

    void register_uninitializer(const string& name, uninit_func func);

    void do_cleanup();
        
}

#endif /* initializer_hpp */
