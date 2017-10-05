//
//  location.hpp
//  spl
//
//  Created by xiangyun.kong on 26/03/2017.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef location_hpp
#define location_hpp

#include <stdio.h>
#include <object/object.h>
#include <object/ptr.h>
#include "file.hpp"

using namespace kxy;

namespace spl {
    
    class location : public object {
    public:
        
    private:
        ptr<file> m_file;
        int m_line;
        int m_line_pos;
        long m_file_pos;
    };
    
}

#endif /* location_hpp */
