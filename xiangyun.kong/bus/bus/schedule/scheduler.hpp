//
//  scheduler.hpp
//  bus
//
//  Created by 孔祥云 on 10/25/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef scheduler_hpp
#define scheduler_hpp

#include <stdio.h>

#include <lib/object/object.hpp>

#include <plugin/event/event.hpp>

#include <class_names.hpp>

using namespace kxy;

namespace pf {
    
    class scheduler {
    public:
        virtual ~scheduler() {}
        
    public:
        virtual void schedule(ptr<object> obj) {}
    };
    
}

#endif /* scheduler_hpp */
