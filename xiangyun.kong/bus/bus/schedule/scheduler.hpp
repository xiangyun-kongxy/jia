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

#include <lib/object/object.h>

#include <plugin/event/event.h>

#include <names.h>

using namespace kxy;

namespace pf {
    
    class scheduler {
    public:
        virtual ~scheduler() {}
        
    public:
        virtual void schedule(ptr<event> evt) {}
        virtual void schedule(ptr<object> obj) {}
    };
    
}

#endif /* scheduler_hpp */
