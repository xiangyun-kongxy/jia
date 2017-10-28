//
//  deliver.hpp
//  bus
//
//  Created by 孔祥云 on 10/26/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef deliver_hpp
#define deliver_hpp

#include <stdio.h>

#include <bus/schedule/scheduler.hpp>

#include <ipc.hpp>

#include <class_names.hpp>

namespace pf {
    
    class deliver : public scheduler {
    public:
        virtual void delive(ptr<object> who) = 0;
        virtual void delive(ptr<object> who, fcallback func) = 0;
        
    };
    
}

#endif /* deliver_hpp */
