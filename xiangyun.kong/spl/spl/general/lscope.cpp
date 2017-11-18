//
//  lscope.cpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "lscope.hpp"

namespace spl {
    
    lscope::lscope(ptr<pptoken> pp, ptr<ltype> type, ptr<lscope> scope) :
    lsymbol(pp, type, scope) {
        
    }
    
    ptr<lsymbol> lscope::find_sym(const string& sname) const {
        return ((lscope*)this)->m_children[sname];
    }
    
    void lscope::add_child(ptr<lsymbol> sym) {
        m_children[sym->sname()] = sym;
    }
    
    void lscope::rm_child(const string& sname) {
        m_children.erase(sname);
    }
}
