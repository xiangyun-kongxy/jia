//
//  lifecycle.hpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef lifecycle_hpp
#define lifecycle_hpp

#include <plugin/plugin.h>

namespace pf {
    
    class lifecycle : public plugin {
    public:
        lifecycle();
        
    public:
        virtual string type() const override ;
        virtual bool is_kind_of(const string &type_name) const override ;
    };
    
}

#endif /* lifecycle_hpp */
