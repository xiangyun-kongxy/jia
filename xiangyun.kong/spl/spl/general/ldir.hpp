//
//  ldir.hpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef ldir_h
#define ldir_h

#include <lib/object/reference.hpp>
#include <lib/object/ptr.hpp>

#include <map>
#include <string>
#include <list>

using namespace std;
using namespace kxy;

namespace spl {
    
    class lfile;
    
    class ldir : public reference {
    public:
        ldir(const string& name, ptr<ldir> path);
        
    public:
        string name() const;
        string sname() const;
        
    public:
        list<ptr<lfile>> files() const;
        list<ptr<ldir>> sub_dir() const;
        ptr<ldir> parent() const;
        
        void add_child(ptr<ldir> dir);
        void rm_child(const string& name);
        
        void add_file(ptr<lfile> file);
        void rm_file(const string& name);
        
    protected:
        string m_name;
        ptr<ldir> m_parent;
        map<string, ptr<ldir>> m_children;
        map<string, ptr<lfile>> m_files;
    };
}

#endif /* ldir_h */
