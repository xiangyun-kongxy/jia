//
//  complier.cpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "bsp_complier.hpp"

#include <lib/fs/file_util.hpp>

#include <spl/general/llocation.hpp>
#include <spl/general/pptoken.hpp>
#include <spl/bsp/lexical/parser/bsp_pp_parser.hpp>

#include <dirent.h>
#include <iostream>

using namespace std;

namespace spl {
namespace bsp {
    
    compiler::compiler() {
        m_root = new ldir("/", nullptr);
    }
    
    void compiler::add_dir(const string &path) {
        for (string file : file_util::file_in_dir(path.c_str(), ".bsp")) {
            add_file(path + "/" + file);
        }
    }
    
    void compiler::add_file(const string &file) {
        ptr<lfile> fd = lfile::parse(m_root, file);
        if (fd != nullptr)
            m_files[fd->sname()] = fd;
    }
    
    ptr<bsp_barren> parse_barren(deque<ptr<pptoken>>::iterator& token,
                                 const deque<ptr<pptoken>>::iterator& end,
                                 ptr<bsp_barren> parent) {
        if ((*token)->is_kind_of("bsp_pp_symbol")) {
            ptr<bsp_barren> bsp = new bsp_barren(*token, parent);
            ++token;
            while (token != end && (*token)->str() != ")") {
                if ((*token)->str() == "(") {
                    ++token;
                    ptr<bsp_barren> child = parse_barren(token, end, bsp);
                    if (child != nullptr) {
                        bsp->add_attr(child);
                    }
                } else if ((*token)->is_kind_of("bsp_pp_op")) {
                    ++token;
                } else if ((*token)->is_kind_of("bsp_pp_comment")) {
                    ++token;
                } else {
                    bsp->add_attr(*token);
                    ++token;
                }
            }
            if (token != end) {
                ++token;
            }
            return bsp;
        }
        return nullptr;
    }
    
    void compiler::compile(ptr<lfile> file) {
        m_files.erase(file->sname());
        
        deque<ptr<pptoken>> pptokens = bsp_pp_parser::parse(file);
        
        deque<ptr<pptoken>>::iterator i = pptokens.begin();
        while (i != pptokens.end()) {
            ptr<pptoken> token = *i;
            if (token->is_kind_of("bsp_pp_op")) {
                if (token->str() == "(") {
                    ++i;
                    ptr<bsp_barren> bsp;
                    bsp = parse_barren(i, pptokens.end(), nullptr);
                    if (bsp != nullptr) {
                        m_barrens.push_back(bsp);
                    }
                } else {
                    // error
                    ++i;
                }
            } else if (token->is_kind_of("bsp_pp_keyword")) {
                if (token->str() == "#include") {
                    token = *(++i);
                    if (token->is_kind_of("bsp_pp_string")) {
                        ptr<lfile> fd = m_files[token->str()];
                        if (fd != nullptr) {
                            compile(fd);
                        }
                    }
                }
                ++i;
            } else if (token->is_kind_of("bsp_pp_comment")) {
                ++i;
            } else {
                // error
                ++i;
            }
        }
    }
    
    void compiler::compile() {
        while (!m_files.empty()) {
            ptr<lfile> file = m_files.begin()->second;
            if (file != nullptr) {
                compile(file);
            } else {
                m_files.erase(m_files.begin());
            }
        }
    }
    
    void compiler::show_barren() {
        for (ptr<bsp_barren> bsp : m_barrens) {
            cout << bsp->str() << endl;
        }
    }
    
}
}
