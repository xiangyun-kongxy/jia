//
//  writable_book.cpp
//  learning
//
//  Created by 孔祥云 on 4/22/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "writable_book.hpp"

namespace mind {
    
    writable_book::writable_book(int size) :
    const_book({}) {
        m_context.resize(size);
        m_version = 0;
    }
    
    ptr<barren> writable_book::write(int pos, ptr<barren> obj) {
        m_lock.lock();
        
        ptr<barren> result = nullptr;
        if (pos < m_context.size()) {
            ptr<barren> result = m_context[pos];
            m_context[pos] = obj;
            ++m_version;
        }
        
        m_lock.unlock();
        return result;
    }
    
    ptr<barren> writable_book::operator[] (int pos) {
        m_lock.lock();
        ptr<barren> result = const_book::operator[](pos);
        m_lock.unlock();
        
        return result;
    }
    
    long writable_book::size() {
        m_lock.lock();
        long result = m_context.size();
        m_lock.unlock();
        
        return result;
    }
    
    long writable_book::version() {
        return m_version;
    }
    
}
