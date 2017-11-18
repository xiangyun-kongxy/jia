//
//  luser_type.hpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef luser_type_hpp
#define luser_type_hpp

#include <spl/general/ltype.hpp>
#include <spl/general/lscope.hpp>

namespace spl {
    
    class luser_type : virtual public ltype, virtual public lsymbol {
    public:
        luser_type(ptr<pptoken> pp, ptr<ltype> type, ptr<lscope> scope):
        ltype(pp->str()),
        lsymbol(pp, type, scope) {
            
        }
        
    public:
        virtual string type() const override {
            return "luser_type";
        }
        
        virtual bool is_kind_of(const string& type_name) const override {
            return  type_name == "luser_type" || ltype::is_kind_of(type_name) ||
                    lsymbol::is_kind_of(type_name);
        }
        
    public:
        virtual string name() const override {
            return lsymbol::name();
        }
        
    };
    
}

#endif /* luser_type_hpp */
