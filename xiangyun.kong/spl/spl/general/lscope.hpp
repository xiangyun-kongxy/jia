//
//  lscope.hpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef lscope_h
#define lscope_h

#include <spl/general/lsymbol.hpp>
#include <spl/general/pptoken.hpp>

#include <map>
#include <string>

using namespace std;

namespace spl {
    
    class lscope : public lsymbol {
    public:
        DECLARE_TYPE(lsymbol, "lscope");
        
    public:
        lscope(ptr<pptoken> pp, ptr<ltype> type, ptr<lscope> scope);
        
    public:
        ptr<lsymbol> find_sym(const string& sname) const;
        
        void add_child(ptr<lsymbol> sym);
        void rm_child(const string& sname);
        
    private:
        map<string, ptr<lsymbol>> m_children;
    };
    
}

#endif /* lscope_h */
