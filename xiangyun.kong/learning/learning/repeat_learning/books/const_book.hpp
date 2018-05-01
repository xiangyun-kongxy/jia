//
//  const_book.hpp
//  learning
//
//  Created by 孔祥云 on 4/22/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef const_book_hpp
#define const_book_hpp

#include <learning/repeat_learning/book.hpp>

namespace mind {
    
    class const_book : public book {
    public:
        const_book(initializer_list<ptr<barren>> init);
        const_book(list<ptr<barren>> init);
        
    public:
        virtual ptr<barren> operator [] (int pos);
        virtual long size();
        virtual long version();
        
    protected:
        vector<ptr<barren>> m_context;
    };
    
}

#endif /* const_book_hpp */
