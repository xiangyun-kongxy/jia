//
//  exe_publish.hpp
//  ps
//
//  Created by xiangyun.kong on 10/28/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef exe_publish_h
#define exe_publish_h

#include <plugin/executor/executor.hpp>

#include <ps/ps.hpp>

namespace pf {

    class publisher : public executor {
    public:
        DECLARE_TYPE(executor, EXE_PUBLISHER);
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<ps> ps = owner;
            ps->publish(evt);
            
            return nullptr;
        }
    };
    
}
#endif /* exe_publish_h */
