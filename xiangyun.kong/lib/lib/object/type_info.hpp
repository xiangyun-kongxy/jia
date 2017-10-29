//
//  type_info.h
//  lib
//
//  Created by 孔祥云 on 11/10/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef type_info_h
#define type_info_h

#include <class_names.hpp>

namespace kxy {
    
#define DECLARE_TYPE(base, inherit_type_name)                           \
public:                                                                 \
    virtual string type() const override {                              \
        return inherit_type_name;                                       \
    }                                                                   \
    virtual bool is_kind_of(const string& type_name) const override {   \
        return type_name == inherit_type_name                           \
        || base::is_kind_of(type_name);                                 \
    }

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
