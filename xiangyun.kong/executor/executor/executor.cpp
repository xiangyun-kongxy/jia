/*
 *  executor.cpp
 *  executor
 *
 *  Created by xiangyun.kong on 10/7/17.
 *  Copyright © 2017 xiangyun.kong. All rights reserved.
 *
 */

#include <iostream>
#include "executor.hpp"
#include "trigger/trigger_execute_barren.hpp"
#include "trigger/trigger_new_barren_function.hpp"
#include "trigger/trigger_new_compound_function.hpp"

#include <functions.h>
#include <names.h>

namespace mind {

    barren_executor::barren_executor() {
        m_event_processor[F_EXECUTE_BARREN] = new execute_barren;
        m_event_processor[F_NEW_BARREN_FUNCTION] = new class new_barren_function;
        m_event_processor[F_NEW_COMPOUND_FUNCTION] = new class new_compound_function;
    }

    void barren_executor::exe_func(ptr<barren> obj) {
        long instruction = (**obj)[0];
        exe_func_inner(instruction, obj);
    }

    void barren_executor::exe_func_inner(long instruction, ptr<barren> obj) {
        map<long, barren_function>::iterator i;
        map<long, list<long>>::iterator it;

        i = m_atom_functions.find(instruction);
        if (i != m_atom_functions.end()) {
            i->second(obj);
        } else {
            it = m_compound_functions.find(instruction);
            if (it != m_compound_functions.end()) {
                for (long ins : it->second) {
                    exe_func_inner(ins, obj);
                }
            }
        }
    }

    void barren_executor::new_barren_function(long instruction,
                                              barren_function func) {
        m_atom_functions[instruction] = func;
    }

    void barren_executor::new_compound_function(long instruction,
                                                const list<long>& body) {
        m_compound_functions[instruction] = body;
    }

    string barren_executor::type() const {
        return PLUGIN_BARREN_EXECUTOR;
    }

    bool barren_executor::is_kind_of(const string &type_name) const {
        return type_name == PLUGIN_BARREN_EXECUTOR || plugin::is_kind_of(type_name);
    }

    extern "C" void* init_barren_executor(void* conf) {
        return new barren_executor;
    }
}
