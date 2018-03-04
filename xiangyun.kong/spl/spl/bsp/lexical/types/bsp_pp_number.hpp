//
//  bsp_pp_number.hpp
//  spl
//
//  Created by 孔祥云 on 11/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef bsp_pp_number_h
#define bsp_pp_number_h

#include <spl/general/pptoken.hpp>

namespace spl {
namespace bsp {
    
    class bsp_pp_number : public pptoken {
    public:
        DECLARE_TYPE(pptoken, "bsp_pp_number");
        
    public:
        bsp_pp_number(const string& str, ptr<llocation> localtion, long num) :
        pptoken(str, localtion) {
            m_number = num;
        }
        
    public:
        long get() const {
            return m_number;
        }
        
    private:
        long m_number;
    };
    
}
}

#endif /* bsp_pp_number_h */
