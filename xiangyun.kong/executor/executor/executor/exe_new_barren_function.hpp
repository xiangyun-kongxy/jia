//
//  exe_new_barren_fuction.hpp
//  executor
//
//  Created by xiangyun.kong on 10/7/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef exe_new_barren_fuction_h
#define exe_new_barren_fuction_h

#include <executor/executor.hpp>

using namespace pf;

namespace mind {

    class new_barren_function : public executor {
    public:
        DECLARE_TYPE(executor, EXE_NEW_BARREN_FUNCTION);
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<serializable> data = evt->param();
            long instruction;
            barren_function func;
            data >> instruction >> (long&)func;
            ((ptr<barren_executor>)owner)->new_barren_function(instruction, func);

            return nullptr;
        }

    };
}

#endif /* exe_new_barren_fuction_h */
