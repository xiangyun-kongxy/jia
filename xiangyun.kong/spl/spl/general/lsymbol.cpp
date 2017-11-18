//
//  lsymbol.cpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "lsymbol.hpp"
#include <spl/general/lscope.hpp>

namespace spl {
    
    lsymbol::lsymbol(ptr<pptoken> pp, ptr<ltype> type, ptr<lscope> scope) {
        m_ppstr = pp;
        m_type = type;
        m_scope = scope;
    }
    
    string lsymbol::name() const {
        if (m_scope != nullptr) {
            return m_scope->name() + ":" + m_ppstr->str();
        } else {
            return m_ppstr->str();
        }
    }
    
    string lsymbol::sname() const {
        return m_ppstr->str();
    }
    
    ptr<llocation> lsymbol::location() const {
        return m_ppstr->location();
    }
    
    void lsymbol::add_reference(ptr<lsymbol> sym) {
        m_reference[sym->name()] = sym;
    }
    
    void lsymbol::rm_reference(const string& name) {
        m_reference.erase(name);
    }
}
