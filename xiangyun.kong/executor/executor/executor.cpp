/*
 *  executor.cpp
 *  executor
 *
 *  Created by xiangyun.kong on 10/7/17.
 *  Copyright © 2017 xiangyun.kong. All rights reserved.
 *
 */

#include <iostream>

#include <executor/executor.hpp>

#include <executor/executor/exe_execute_barren.hpp>
#include <executor/executor/exe_new_barren_function.hpp>
#include <executor/function/barren_call.hpp>

#include <barren/util/barren_io.hpp>

#include <predefined_barren.hpp>
#include <ipc.hpp>

namespace mind {
    extern map<long, bfunction> g_bfunctions;
    
    barren_executor::barren_executor() {
        m_executors[M_EXECUTE_BARREN]        = new class execute_barren;
        m_executors[M_NEW_BARREN_FUNCTION]   = new class new_barren_function;
    }
    
    void barren_executor::exe_func(ptr<barren> obj) {
        ptr<barren> result;
        
        ptr<barren_call> func = obj;
        if (func->is_call()) {
            deque<ptr<barren>> params;
            for (long i = 3; i < func->size(); ++i) {
                if ((**func)[i] > 0) {
                    params.push_back(load_barren((**func)[i]));
                } else if ((**func)[i] <= 0) {
                    params.push_back(nullptr);
                }
            }
            result = func->call(params);
        } else  {
            result = func;
        }
        
        ptr<barren> rr = new barren({0L,
            BARREN_CALL_RESULT, obj->id(), result->id()});
        save_barren(rr);
        broadcast(M_BARREN_EXECUTED, rr);
    }

    void barren_executor::new_barren_function(long instruction,
                                              bfunction func) {
        g_bfunctions[instruction] = func;
    }


    extern "C" void* init_barren_executor(void* conf) {
        return new barren_executor;
    }
}
