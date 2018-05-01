/*
 *  learning.cpp
 *  learning
 *
 *  Created by 孔祥云 on 3/24/18.
 *  Copyright © 2018 孔祥云. All rights reserved.
 *
 */

#include <learning/executor/exe_add_book.hpp>
#include <learning/executor/exe_get_book.hpp>
#include <learning/executor/exe_rm_book.hpp>
#include "learning.hpp"

#include <learning/repeat_learning/distil/cartesian.hpp>
#include <learning/repeat_learning/distil/bin_combine.hpp>
#include <learning/repeat_learning/distil/heaping.hpp>

namespace mind {
    
    learning::learning() {
        m_books = new book_manager;
      
        m_executors[M_ADD_BOOK] = new exe_add_book;
        m_executors[M_GET_BOOK] = new exe_get_book;
        m_executors[M_RM_BOOK]  = new exe_rm_book;
    }

    ptr<book_manager> learning::get_books() {
        return m_books;
    }
}
