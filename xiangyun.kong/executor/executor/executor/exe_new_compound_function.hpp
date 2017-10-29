//
//  exe_new_compound_function.hpp
//  executor
//
//  Created by xiangyun.kong on 10/7/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef exe_new_compound_function_h
#define exe_new_compound_function_h

#include <executor/executor.hpp>

using namespace pf;

namespace mind {

    class new_compound_function : public executor {
    public:
        DECLARE_TYPE(executor, EXE_NEW_COMPOUND_FUNCTION);
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<barren_executor> executor = owner;
            ptr<serializable> data = evt->param();
            long instruction;
            list<long> body;
            data >> instruction >> body;
            executor->new_compound_function(instruction, body);

            return nullptr;
        }

    };
}

#endif /* exe_new_compound_function_h */
