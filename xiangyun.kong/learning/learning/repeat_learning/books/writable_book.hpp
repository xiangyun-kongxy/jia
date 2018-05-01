//
//  writable_book.hpp
//  learning
//
//  Created by 孔祥云 on 4/22/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef writable_book_hpp
#define writable_book_hpp

#include <learning/repeat_learning/books/const_book.hpp>

#include <lib/lock/spinlock.hpp>

using namespace kxy;

namespace mind {
    
    class writable_book : public const_book {
    public:
        writable_book(int size);
        
    public:
        virtual ptr<barren> operator [] (int pos) override;
        virtual long size() override;
        virtual long version() override;
        
    public:
        ptr<barren> write(int pos, ptr<barren> obj);
        
    protected:
        spin_mutex m_lock;
        long m_version;
    };
    
}

#endif /* writable_book_hpp */
