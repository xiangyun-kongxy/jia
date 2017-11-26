//
//  bsp_pp_string.hpp
//  spl
//
//  Created by 孔祥云 on 11/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef bsp_pp_string_h
#define bsp_pp_string_h

#include <spl/general/pptoken.hpp>

namespace spl {
namespace bsp {
    
    class bsp_pp_string : public pptoken {
    public:
        DECLARE_TYPE(pptoken, "bsp_pp_string");
        
    public:
        bsp_pp_string(const string& name, ptr<llocation> location)
        : pptoken(name, location) {
            
        }
    };
    
}
}

#endif /* bsp_pp_string_h */
