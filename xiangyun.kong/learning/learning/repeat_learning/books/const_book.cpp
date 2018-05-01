//
//  const_book.cpp
//  learning
//
//  Created by 孔祥云 on 4/22/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "const_book.hpp"

namespace mind {
    
    const_book::const_book(initializer_list<ptr<barren>> init) {
        m_context.resize(init.size());
        for (ptr<barren> b : init) {
            m_context.push_back(b);
        }
    }
    
    const_book::const_book(list<ptr<barren>> init) {
        m_context.resize(init.size());
        for (ptr<barren> b : init) {
            m_context.push_back(b);
        }
    }
    
    ptr<barren> const_book::operator [] (int pos) {
        if (pos < size())
            return m_context[pos];
        else
            return nullptr;
    }
    
    long const_book::size() {
        return m_context.size();
    }
    
    long const_book::version() {
        return 0;
    }
    
}
