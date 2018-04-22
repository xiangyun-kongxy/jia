//
//  learning_book.cpp
//  learning
//
//  Created by 孔祥云 on 4/22/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "learning_book.hpp"

namespace mind {
    
    learning_book::learning_book() {
        m_version = 0;
    }
    
    learning_book::~learning_book() {
        
    }
    
    void learning_book::set_opt(ptr<distil> opt) {
        m_opt = opt;
    }
    
    void learning_book::set_opd(const vector<ptr<book> > &opd) {
        m_opd = opd;
    }
    
    long learning_book::size() {
        try_update_book();
        return m_cached->size();
    }
    
    long learning_book::version() {
        try_update_book();
        return m_version;
    }
    
    ptr<barren> learning_book::operator[](int pos) {
        try_update_book();
        return (**m_cached)[pos];
    }
    
    void learning_book::try_update_book() {
        long ver = 1;
        for (ptr<book> d : m_opd) {
            if (d->version() > ver)
                ver = d->version();
        }
        if (ver > version()) {
            m_cached = m_opt->perform(m_opd);
            m_version = ver;
        }
    }
}
