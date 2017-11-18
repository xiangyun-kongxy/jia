//
//  lfile.cpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "lfile.hpp"

namespace spl {
    
    lfile::lfile(const string& name, ptr<ldir> path) {
        m_parent = path;
        m_name = name;
        m_source_code = nullptr;
    }
    
    lfile::~lfile() {
        delete[] m_source_code;
    }
    
    string lfile::name() const {
        return m_parent->name() + "/" + m_name;
    }
    
    string lfile::sname() const {
        return m_name;
    }
    
    ptr<ldir> lfile::path() const {
        return m_parent;
    }
    
    char* lfile::source_code() {
        if (m_source_code != nullptr) {
            return m_source_code;
        } else {
            m_source_code = file_util::read_to_buf(this->name());
            return m_source_code;
        }
    }
    
    void lfile::release_source_code() {
        delete [] m_source_code;
        m_source_code = nullptr;
    }
}
