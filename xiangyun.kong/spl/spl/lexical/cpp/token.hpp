//
//  token.hpp
//  spl
//
//  Created by 孔祥云 on 3/26/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef token_hpp
#define token_hpp

#include <stdio.h>
#include "location.hpp"

namespace spl {
    
    class token {
    public:
        
        template<typename ty>
        ty value();
        
    protected:
        ptr<location> m_location;
        string m_word;
    };
    
}

#endif /* token_hpp */
