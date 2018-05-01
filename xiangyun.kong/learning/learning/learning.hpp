/*
 *  learning.hpp
 *  learning
 *
 *  Created by 孔祥云 on 3/24/18.
 *  Copyright © 2018 孔祥云. All rights reserved.
 *
 */

#ifndef learning_
#define learning_

#include <plugin/plugin/plugin.hpp>
#include <learning/repeat_learning/manager/book_manager.hpp>
#include <lib/identifier/id_name.hpp>
#include <messages.hpp>

using namespace pf;
using namespace kxy;

namespace mind {
    
    class learning : public pf::plugin {
    public:
        DECLARE_TYPE(pf::plugin, PLUGIN_LEARNING)
        
        IMPL_BEGIN
            IMPL_F(T_NONE, M_ADD_BOOK, T_STR, T_USER)
            IMPL_F(T_USER, M_GET_BOOK, T_STR)
            IMPL_F(T_NONE, M_RM_BOOK, T_STR)
        IMPL_END
        
    public:
        learning();
        
    public:
        virtual list<ptr<identifier>> depend_on() const override {
            return list<ptr<identifier>>({
                new id_name(PLUGIN_BARREN_CACHE),
                new id_name(PLUGIN_CONFIG_CENTER)});
        }
        
    public:
        ptr<book_manager> get_books();
        
    private:
        ptr<book_manager> m_books;
        
    };
         
}

#endif
