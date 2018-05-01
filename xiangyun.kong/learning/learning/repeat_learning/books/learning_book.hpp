//
//  learning_book.hpp
//  learning
//
//  Created by 孔祥云 on 4/22/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef learning_book_hpp
#define learning_book_hpp

#include <learning/repeat_learning/books/writable_book.hpp>
#include <learning/repeat_learning/distil.hpp>

namespace mind {
    
    class learning_book : public writable_book {
    public:
        learning_book();
        
    public:
        void set_opt(ptr<distil> opt);
        void set_opd(const vector<ptr<book>>& opd);
        
    public:
        virtual ptr<barren> operator [] (int pos) override;
        virtual long size() override;
        virtual long version() override;
        
    protected:
        void try_update_book();
        
    protected:
        ptr<distil> m_opt;
        vector<ptr<book>> m_opd;
    };
}

#endif /* learning_book_hpp */
