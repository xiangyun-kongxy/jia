//
//  file.hpp
//  spl
//
//  Created by xiangyun.kong on 26/03/2017.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef file_hpp
#define file_hpp

#include <lib/fs/file_util.hpp>

#include <spl/general/ldir.hpp>

using namespace kxy;

namespace spl {
    
    class lfile : public reference {
    public:
        lfile(const string& name, ptr<ldir> path);
        ~lfile();
        
    public:
        string name() const;
        string sname() const;
        
    public:
        ptr<ldir> path() const;
            
        char* source_code();
        void release_source_code();
        
    protected:
        ptr<ldir> m_parent;
        string m_name;
        
        char* m_source_code;
    };
    
}

#endif /* file_hpp */
