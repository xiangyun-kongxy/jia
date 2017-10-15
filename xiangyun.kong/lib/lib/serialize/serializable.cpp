//
//  serializable.cpp
//  lib
//
//  Created by 孔祥云 on 7/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "serializable.hpp"
#include <string.h>

namespace kxy {
    
    serializable::serializable() {
    }
    
    serializable::serializable(const char* buf) {
        char* copy = new char[strlen(buf) + 1];
        strcpy(copy, buf);
        
        char* context;
        char* split = strtok_r(copy, SS1, &context);
        while (split != nullptr) {
            m_buf.push_back(split);
            split = strtok_r(NULL, SS1, &context);
        }
    }
    
}
