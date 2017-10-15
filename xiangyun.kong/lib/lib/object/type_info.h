//
//  type_info.h
//  lib
//
//  Created by 孔祥云 on 11/10/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef type_info_h
#define type_info_h

#include <names.h>

namespace kxy {
    
    class type_info {
    public:
        virtual ~type_info() {
            
        }
        
    public:
        virtual string type() const {
            return TYPE_INFO;
        }
        
        virtual bool is_kind_of(const string& type_name) const {
            return type_name == TYPE_INFO;
        }
    };
    
}

#endif /* type_info_h */
