//
//  id_name.h
//  lib
//
//  Created by 孔祥云 on 11/30/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef id_name_h
#define id_name_h

#include "identifier.hpp"

namespace kxy {
    
    class id_name : public identifier {
    public:
        DECLARE_TYPE(identifier, ID_NAME);
        
    public:
        id_name(const string& name, ptr<identifier> base = nullptr)
        :   identifier(base),
            m_name(name) {
        }
        
    public:
        virtual bool match(ptr<object> obj) override {
            return m_name == obj->name() && identifier::match(obj);
        }
        
        virtual string name() const override {
            return m_name;
        }
        
    protected:
        string m_name;
    };
    
}

#endif /* id_name_h */
