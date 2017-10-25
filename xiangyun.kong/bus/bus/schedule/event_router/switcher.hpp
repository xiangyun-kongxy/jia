//
//  switcher.hpp
//  bus
//
//  Created by 孔祥云 on 10/25/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef switcher_hpp
#define switcher_hpp

#include <stdio.h>

#include <bus/schedule/scheduler.hpp>

namespace pf {
    
    class switcher : public scheduler {
    public:
        virtual void update_plugins() = 0;
    };
}

#endif /* switcher_hpp */
