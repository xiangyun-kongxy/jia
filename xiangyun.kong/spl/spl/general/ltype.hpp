//
//  ltype.hpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef ltype_h
#define ltype_h

#include <lib/object/object.hpp>

using namespace kxy;

namespace spl {
    
    class ltype : public object {
    public:
        DECLARE_TYPE(object, "ltype");
        
    public:
        ltype(const string& name) {
            m_name = name;
        }
        
    public:
        virtual string name() const override {
            return m_name;
        }
        
    protected:
        string m_name;
    };
    
}

#endif /* ltype_h */
