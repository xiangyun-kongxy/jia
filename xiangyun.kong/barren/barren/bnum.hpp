//
//  bnum.hpp
//  barren
//
//  Created by 孔祥云 on 5/1/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef bnum_h
#define bnum_h

namespace mind {
    
    class bnum {
    public:
        enum num_type {
            NT_REF,
            NT_PARAM,
            NT_NUM,
            NT_BARREN,
        };
        
        static const long NPS = -1;
        static const long NRS = -100;
        static const long NNS = -10000;
        
    public:
        static long encode(long num, num_type type) {
            switch (type) {
                case NT_PARAM:
                    if (num < 99)
                        return NPS - num;
                    else
                        return 0;
                case NT_REF:
                    if (num < 9999)
                        return NRS - num;
                    else
                        return 0;
                case NT_NUM:
                    return NNS - num;
                case NT_BARREN:
                default:
                    return num;
            }
        }
        
        static long decode(long num, num_type* type) {
            num_type t;
            if (type == nullptr)
                type = &t;
            
            if (num > NPS) {
                num = num;
                *type = NT_BARREN;
            } else if (num > NRS) {
                num = NPS - num;
                *type = NT_PARAM;
            } else if (num > NNS) {
                num = NRS - num;
                *type = NT_REF;
            } else {
                num = NNS - num;
                *type = NT_NUM;
            }
            return num;
        }
    };
    
}

#endif /* bnum_h */
