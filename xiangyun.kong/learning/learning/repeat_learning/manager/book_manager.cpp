//
//  book_manager.cpp
//  learning
//
//  Created by 孔祥云 on 4/29/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "book_manager.hpp"

namespace mind {
    
    ptr<book> book_manager::get(const string &name) {
        return m_books[name];
    }
    
    void book_manager::add(const string &name, ptr<mind::book> bk) {
        m_books[name] = bk;
    }
    
    void book_manager::remove(const string &name) {
        m_books.erase(name);
    }
}
