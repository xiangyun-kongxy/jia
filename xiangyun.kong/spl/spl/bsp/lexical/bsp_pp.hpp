//
//  bsp_pp.hpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef bsp_pp_hpp
#define bsp_pp_hpp

#include <spl/general/pptoken.hpp>

#include <deque>

using namespace std;

namespace spl {
namespace bsp {
    
    class bsp_pp {
    public:
        static deque<ptr<pptoken>> complie(char* buf);
    };
    
}
}

#endif /* bsp_pp_hpp */
