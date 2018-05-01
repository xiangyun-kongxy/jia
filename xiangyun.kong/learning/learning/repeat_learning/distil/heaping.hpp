//
//  heaping.hpp
//  learning
//
//  Created by 孔祥云 on 5/1/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef heaping_h
#define heaping_h

#include <learning/repeat_learning/distil.hpp>
#include <learning/repeat_learning/books/const_book.hpp>
#include <key_barren.hpp>

namespace mind {
    
    class heaping : public distil {
    public:
        virtual ptr<book> perform(const vector<ptr<book>>& books) {
            if (books.size() == 1) {
                long bs = books[0]->size();
                list<ptr<barren>> brs;
                for (int i = 0; i < bs - 1; ++i) {
                    for (int l = 1; l < bs - i; ++i) {
                        vector<long> ids(l + 1);
                        ids[0] = m_id_relate;
                        for (int j = 0; j < l; ++j)
                            ids[1 + j] = (**books[0])[i+j]->id();
                        brs.push_back(new barren(ids));
                    }
                }
                return new const_book(brs);
            } else {
                return new const_book({});
            }
        }
        
    public:
        heaping() {
            m_id_relate = barren::load(br_relate)->id();
        }
        
    protected:
        long m_id_relate;
    };
    
}

#endif /* heaping_h */
