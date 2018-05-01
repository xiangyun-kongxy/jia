//
//  bin_combine.hpp
//  learning
//
//  Created by 孔祥云 on 4/29/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef bin_combine_h
#define bin_combine_h

#include <learning/repeat_learning/distil.hpp>
#include <learning/repeat_learning/books/const_book.hpp>
#include <learning/repeat_learning/distil/heaping.hpp>
#include <key_barren.hpp>

namespace mind {
    
    class bin_combine : public heaping {
    public:
        virtual ptr<book> perform(const vector<ptr<book>>& books) {
            if (books.size() == 1) {
                list<ptr<barren>> brs;
                for (int i = 0; i < books[0]->size() - 1; ++i) {
                    brs.push_back(new barren({m_id_relate,
                                        (**books[0])[i]->id(),
                                        (**books[0])[i+1]->id()}));
                }
                return new const_book(brs);
            } else {
                return new const_book({});
            }
        }
    };
    
}

#endif /* bin_combine_h */
