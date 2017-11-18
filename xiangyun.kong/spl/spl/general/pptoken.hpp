//
//  pptoken.hpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef pptoken_hpp
#define pptoken_hpp

#include <spl/general/llocation.hpp>

namespace spl {
    
    class pptoken : public reference {
    public:
        pptoken(const string& str, ptr<llocation> location);
        
    public:
        string str() const;
        ptr<llocation> location() const;
            
    protected:
        string m_ppstr;
        ptr<llocation> m_location;
    };
    
}

#endif /* pptoken_hpp */