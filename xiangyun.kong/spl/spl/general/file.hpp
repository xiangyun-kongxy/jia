//
//  file.hpp
//  spl
//
//  Created by xiangyun.kong on 26/03/2017.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef file_hpp
#define file_hpp

#include <stdio.h>
#include <lib/object/object.hpp>

using namespace kxy;

namespace spl {
    
    class file : public object {
    public:
        
    private:
        string m_path;
        string m_name;
        string m_ext;
        const char* m_text;
        long m_length;
    };
    
}

#endif /* file_hpp */
