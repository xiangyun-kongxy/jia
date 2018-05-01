//
//  cartesian.hpp
//  learning
//
//  Created by 孔祥云 on 4/29/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef cartesian_h
#define cartesian_h

#include <learning/repeat_learning/distil.hpp>
#include <learning/repeat_learning/books/const_book.hpp>
#include <key_barren.hpp>

namespace mind {
    
    class cartesian : public distil {
    public:
        virtual ptr<book> perform(const vector<ptr<book>>& books) {
            if (books.size() == 2) {
                list<ptr<barren>> brs;
                for (int i = 0; i < books[0]->size(); ++i) {
                    for (int j = 0; j < books[1]->size(); ++j) {
                        brs.push_back(new barren({
                            barren::load(br_relate)->id(),
                            (**books[0])[i]->id(),
                            (**books[1])[j]->id()}));
                    }
                }
                return new const_book(brs);
            } else {
                return new const_book({});
            }
        }
    };
    
}

#endif /* cartesian_h */
