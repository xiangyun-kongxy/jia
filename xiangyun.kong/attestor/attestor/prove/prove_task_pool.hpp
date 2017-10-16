//
//  prove_task_pool.hpp
//  attestor
//
//  Created by 孔祥云 on 3/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef prove_task_pool_hpp
#define prove_task_pool_hpp

#include <lib/container/cqueue.h>

#include <attestor/prove/prove_context.hpp>

#include <map>
#include <set>

using namespace kxy;
using namespace std;

namespace mind {
    
    template<typename ty>
    class prove_task_pool : public cqueue<ty> {
    public:
        void add_prove_context(ptr<prove_context> context);
        void proved(ptr<prove_context> context);
        
    private:
        set<ptr<prove_context>> m_tasks;
        set<ptr<prove_context>> m_contexts;
        multimap<long, ptr<prove_context>> m_context_index;
    };
}

#endif /* prove_task_pool_hpp */
