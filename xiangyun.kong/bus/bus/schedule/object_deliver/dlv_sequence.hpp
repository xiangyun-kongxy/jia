//
//  dlv_sequence.hpp
//  bus
//
//  Created by 孔祥云 on 10/26/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef dlv_sequence_h
#define dlv_sequence_h

#include <bus/schedule/object_deliver/deliver.hpp>

#include <ipc.hpp>

namespace pf {
    
    class dlv_sequence : public deliver {
    public:
        
    public:
        virtual void delive(ptr<object> what) override {
        }
        
        virtual void delive(ptr<object> what, fcallback func) override {
        }
        
        virtual void schedule(ptr<object> obj) override {
        }
        
    private:
    };
    
}

#endif /* dlv_sequence_h */
