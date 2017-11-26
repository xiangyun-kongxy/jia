//
//  bsp_pp_op.h
//  spl
//
//  Created by 孔祥云 on 11/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef bsp_pp_op_h
#define bsp_pp_op_h

#include <spl/general/pptoken.hpp>

namespace spl {
namespace bsp {
    
    class bsp_pp_op : public pptoken {
    public:
        DECLARE_TYPE(pptoken, "bsp_pp_op");
        
    };
    
}
}

#endif /* bsp_pp_op_h */
