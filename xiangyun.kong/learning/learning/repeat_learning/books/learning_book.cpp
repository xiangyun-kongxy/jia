//
//  learning_book.cpp
//  learning
//
//  Created by 孔祥云 on 4/22/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "learning_book.hpp"

namespace mind {
    
    learning_book::learning_book() :
    writable_book(1) {
        
    }
    
    void learning_book::set_opt(ptr<distil> opt) {
        m_opt = opt;
    }
    
    void learning_book::set_opd(const vector<ptr<book> > &opd) {
        m_opd = opd;
    }
    
    long learning_book::size() {
        try_update_book();
        return writable_book::size();
    }
    
    long learning_book::version() {
        try_update_book();
        return writable_book::version();
    }
    
    ptr<barren> learning_book::operator[](int pos) {
        try_update_book();
        return writable_book::operator[](pos);
    }
    
    void learning_book::try_update_book() {
        long ver = 1;
        for (ptr<book> d : m_opd) {
            if (d->version() > ver)
                ver += d->version();
        }
        if (ver > m_version) {
            ptr<book> cache = m_opt->perform(m_opd);
            
            m_lock.lock();
            
            m_version = ver;
            m_context.resize(cache->size());
            for (int i = 0; i < cache->size(); ++i) 
                m_context[i] = (**cache)[i];
            
            m_lock.unlock();
        }
    }
}
