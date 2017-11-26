//
//  bsp_pp_comment.hpp
//  spl
//
//  Created by 孔祥云 on 11/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef bsp_pp_comment_h
#define bsp_pp_comment_h

#include <spl/general/pptoken.hpp>

namespace spl {
namespace bsp {
    
    class bsp_pp_comment : public pptoken {
    public:
        DECLARE_TYPE(pptoken, "bsp_pp_comment");
        
    };
    
}
}

#endif /* bsp_pp_comment_h */
