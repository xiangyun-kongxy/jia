//
//  nlg_status.hpp
//  learning
//
//  Created by 孔祥云 on 4/14/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef nlg_status_h
#define nlg_status_h

namespace mind {
        
        enum nlg_status {
                NLS_GUESS               = 1 << 0,
                NLS_PROVING             = 1 << 1,
                NLS_TRY_USE             = 1 << 2,
                
                NLS_PROVED              = 1 << 8,
                NLS_FIRST_CLASS         = 1 << 9,
                NLS_GENETIC             = 1 << 10,
                
                NLS_BY_CASE             = 1 << 16,
                NLS_WRONG               = 1 << 17,
                NLS_REMOVING            = 1 << 18,
                
                NLS_CORRECTING          = 1 << 24,
        };
}

#endif /* nlg_status_h */
