//
//  book.hpp
//  learning
//
//  Created by 孔祥云 on 4/22/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef book_h
#define book_h

#include <lib/object/reference.hpp>
#include <lib/object/ptr.hpp>

#include <barren/barren.hpp>

using namespace kxy;

namespace mind {
    
    class book : public reference {
    public:
        virtual ~book() {}
    public:
        virtual ptr<barren> operator [] (int pos) = 0;
        virtual long size() = 0;
        virtual long version() = 0;
    };
    
}

#endif /* book_h */
