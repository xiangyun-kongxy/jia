/*
 *  executor.hpp
 *  executor
 *
 *  Created by xiangyun.kong on 10/7/17.
 *  Copyright © 2017 xiangyun.kong. All rights reserved.
 *
 */

#ifndef executor_
#define executor_

#include <plugin/plugin/plugin.hpp>
#include <barren/barren.hpp>

/* The classes below are exported */
#pragma GCC visibility push(default)

using namespace pf;

namespace mind {

    typedef void (*barren_function)(ptr<barren>);
    
    class barren_executor : public plugin {
    public:
        barren_executor();
        DECLARE_TYPE(plugin, PLUGIN_BARREN_EXECUTOR);
        
    public:
        void exe_func(ptr<barren>);
        void new_barren_function(long, barren_function);
        void new_compound_function(long, const list<long>&);

    private:
        void exe_func_inner(long, ptr<barren>);

    private:
        map<long, barren_function> m_atom_functions;
        map<long, list<long>> m_compound_functions;
    };
}

#pragma GCC visibility pop
#endif
