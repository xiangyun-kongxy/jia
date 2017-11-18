//
//  lsymbol.hpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef lsymbol_h
#define lsymbol_h

#include <lib/object/ptr.hpp>
#include <spl/general/ltype.hpp>
#include <spl/general/pptoken.hpp>

#include <map>
#include <string>

using namespace std;
using namespace kxy;

namespace spl {
    
    class lscope;
    
    class lsymbol : public object {
    public:
        DECLARE_TYPE(object, "lsymbol");
        
    public:
        lsymbol(ptr<pptoken> pp, ptr<ltype> type, ptr<lscope> scope);
        
    public:
        virtual string name() const override;
        virtual string sname() const;
        ptr<llocation> location() const;
        
    public:
        void add_reference(ptr<lsymbol> sym);
        void rm_reference(const string& name);
        
    protected:
        ptr<pptoken> m_ppstr;
        ptr<ltype> m_type;
        ptr<lscope> m_scope;
        map<string, ptr<lsymbol>> m_reference;
    };
    
}

#endif /* lsymbol_h */
