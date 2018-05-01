//
//  book_manager.hpp
//  learning
//
//  Created by 孔祥云 on 4/29/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef book_manager_hpp
#define book_manager_hpp

#include <map>
#include <string>
#include <learning/repeat_learning/book.hpp>

using namespace std;

namespace mind {
    
    class book_manager : public kxy::reference {
    public:
        ptr<book> get(const string& name);
        void add(const string& name, ptr<book> bk);
        void remove(const string& name);
        
    protected:
        map<string, ptr<book>> m_books;
    };
    
}

#endif /* book_manager_hpp */
