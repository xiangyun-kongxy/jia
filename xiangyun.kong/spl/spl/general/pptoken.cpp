//
//  pptoken.cpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "pptoken.hpp"

namespace spl {
    
    pptoken::pptoken(const string& str, ptr<llocation> location) {
        m_ppstr = str;
        m_location = location;
    }
    
    string pptoken::str() const {
        return m_ppstr;
    }
    
    ptr<llocation> pptoken::location() const {
        return m_location;
    }
    
}
