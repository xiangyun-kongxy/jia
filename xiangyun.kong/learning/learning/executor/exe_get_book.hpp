//
//  exe_get_book.hpp
//  learning
//
//  Created by 孔祥云 on 4/29/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef exe_get_book_h
#define exe_get_book_h

#include <plugin/executor/executor.hpp>
#include <plugin/response/simple_response.hpp>
#include <errors.hpp>

#include <learning/repeat_learning/book.hpp>
#include <learning/learning.hpp>

using namespace pf;

namespace mind {
    
    class exe_get_book : public executor {
    public:
        DECLARE_TYPE(executor, "exe_get_book");
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<serializable> param = evt->param();
            string name;
            ptr<book> bk = nullptr;
            param >> name;
            
            if (name != "") {
                bk = ((ptr<learning>)owner)->get_books()->get(name);
            }
            return new simple_response(evt, EC_OK, EM_OK, param << bk);
        }
    };
}

#endif /* exe_get_book_h */
