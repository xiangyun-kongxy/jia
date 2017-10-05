//
//  decl_serializable.h
//  lib
//
//  Created by 孔祥云 on 7/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef decl_serializable_h
#define decl_serializable_h

#define DECL_SERIALIZE(class, ar, ins, ...)                                     \
    friend serializable& operator << (serializable& ar, const class& ins) {     \
        __VA_ARGS__;                                                            \
        return ar;                                                              \
    }

#define DECL_DESERIALIZE(class, ar, ins, ...)                                   \
    friend serializable& operator >> (serializable& ar, class& ins) {           \
        __VA_ARGS__;                                                            \
        return ar;                                                              \
    }

#endif /* decl_serializable_h */
