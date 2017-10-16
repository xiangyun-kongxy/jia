//
//  prove_context.hpp
//  attestor
//
//  Created by 孔祥云 on 3/16/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef prove_context_hpp
#define prove_context_hpp

#include <stdio.h>
#include <map>

#include <lib/object/object.h>
#include <lib/object/ptr.h>

#include <barren/barren.hpp>


using namespace kxy;
using namespace std;

namespace mind {
    
    class sub_prove_context {
    private:
        sub_prove_context* m_next;
        ptr<class prove_context> m_to_be_proved;
        map<long,long> m_para_mapping;
    };
    
    class prove_context : public object {
    public:
    private:
        ptr<barren> m_to_be_proved;
        list<sub_prove_context> m_sub_prove;
        ptr<prove_context> m_parent;
    };
}

#endif /* prove_context_hpp */
