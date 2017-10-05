//
//  id_any.h
//  lib
//
//  Created by 孔祥云 on 11/30/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef id_any_h
#define id_any_h

#include "identifier.h"

namespace kxy {
    
    class id_any : public identifier {
    public:
        id_any(ptr<identifier> base = nullptr) : identifier(base) {
        }
        
    public:
        virtual bool match(ptr<object> obj) override {
            return identifier::match(obj);
        }
        
        virtual string type() const override {
            return "id_any";
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "id_any" || identifier::is_kind_of(type_name);
        }
        
    };
    
}

#endif /* id_any_h */
