//
//  bsp_pp_keywork.hpp
//  spl
//
//  Created by 孔祥云 on 11/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef bsp_pp_keywork_h
#define bsp_pp_keywork_h

#include <spl/general/pptoken.hpp>

namespace spl {
namespace bsp {
    
    class bsp_pp_keywork : public pptoken {
    public:
        DECLARE_TYPE(pptoken, "bsp_pp_keywork");
        
    public:
        bsp_pp_keywork(const string& name, ptr<llocation> location) :
        pptoken(name, location) {
        }
    };
    
}
}

#endif /* bsp_pp_keywork_h */
