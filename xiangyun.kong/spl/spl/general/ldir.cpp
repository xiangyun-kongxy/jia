//
//  ldir.cpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "ldir.hpp"

#include <spl/general/lfile.hpp>

namespace spl {
    
    ldir::ldir(const string& name, ptr<ldir> path) {
        m_name = name;
        m_parent = path;
    }
    
    string ldir::name() const {
        if (m_parent != nullptr) {
            return m_parent->name() + "/" + m_name;
        } else {
            return m_name;
        }
    }
    
    string ldir::sname() const {
        return m_name;
    }
    
    list<ptr<lfile>> ldir::files() const {
        list<ptr<lfile>> result;
        
        for(pair<string, ptr<lfile>> value : m_files) {
            result.push_back(value.second);
        }
        
        return result;
    }
    
    list<ptr<ldir>> ldir::sub_dir() const {
        list<ptr<ldir>> result;
        
        for (pair<string, ptr<ldir>> value : m_children) {
            result.push_back(value.second);
        }
        
        return result;
    }
    
    ptr<ldir> ldir::parent() const {
        return m_parent;
    }
    
    void ldir::add_child(ptr<ldir> dir) {
        m_children[dir->sname()] = dir;
    }
    
    void ldir::rm_child(const string& name) {
        m_children.erase(name);
    }
    
    void ldir::add_file(ptr<lfile> file) {
        m_files[file->sname()] = file;
    }
    
    void ldir::rm_file(const string& name) {
        m_files.erase(name);
    }
    
}
