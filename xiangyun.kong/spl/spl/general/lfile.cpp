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
    
    ptr<lfile> add_file(ptr<ldir> root, const char* file) {
        if (*file == '/') {
            const char* p = strchr(++file, '/');
            while (p != nullptr) {
                string dir(file, p - file);
                for (ptr<ldir> d : root->sub_dir()) {
                    if (d->name() == dir) {
                        root = d;
                        break;
                    }
                }
                if (root->name() != dir) {
                    ptr<ldir> ndir = new ldir(dir, root);
                    root = ndir;
                }
                
                file = p + 1;
                p = strchr(file, '/');
            }
            return new lfile(file, root);
        }
        return nullptr;
    }
    
    list<ptr<lfile>> lfile::parse(ptr<ldir> root, const list<string> &files) {
        list<ptr<lfile>> lfiles;
        if (root == nullptr)
            root = new ldir("/", nullptr);
        for (string f : files) {
            ptr<lfile> file = add_file(root, f.c_str());
            if (file != nullptr) {
                lfiles.push_back(file);
            }
        }
        return lfiles;
    }
    
    ptr<lfile> lfile::parse(ptr<ldir> root, const string &file) {
        if (root == nullptr)
            root = new ldir("/", nullptr);
        return add_file(root, file.c_str());
    }
}
