//
//  id_any.h
//  lib
//
//  Created by 孔祥云 on 11/30/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef id_any_h
#define id_any_h

#include "identifier.hpp"

namespace kxy {
    
    class id_any : public identifier {
    public:
        DECLARE_TYPE(identifier, ID_ANY);
        
    public:
        id_any(ptr<identifier> base = nullptr) : identifier(base) {
        }
        
    public:
        virtual bool match(ptr<object> obj) override {
            return identifier::match(obj);
        }
        
    public:
        virtual string name() const override {
            return "*";
        }
    };
    
}

#endif /* id_any_h */
