//
//  exe_execute_barren.hpp
//  executor
//
//  Created by xiangyun.kong on 10/7/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef exe_execute_barren_h
#define exe_execute_barren_h

#include <executor/executor.hpp>

using namespace pf;

namespace mind {

    class execute_barren : public executor {
    public:
        DECLARE_TYPE(executor, EXE_EXECUTE_BARREN);
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<serializable> data = evt->param();
            ptr<barren> br;
            data >> br;
            ((ptr<barren_executor>)owner)->exe_func(br);
            
            return nullptr;
        }

    };
}

#endif /* exe_execute_barren_h */
