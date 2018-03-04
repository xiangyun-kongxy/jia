//
//  bsp_barren.hpp
//  spl
//
//  Created by 孔祥云 on 2/25/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef bsp_barren_h
#define bsp_barren_h

#include <spl/bsp/lexical/types/bsp_pp_symbol.hpp>

namespace spl {
    namespace bsp {
        
        class bsp_barren : public pptoken {
        public:
            DECLARE_TYPE(pptoken, "bsp_barren");
            
        public:
            bsp_barren(ptr<bsp_pp_symbol> symbol, ptr<bsp_barren> parent) :
            pptoken(symbol->str(), symbol->location()) {
                
            }
            
        public:
            void add_attr(ptr<pptoken> token) {
                m_attrs.push_back(token);
            }
            
        public:
            virtual string str() const override {
                string s = "(";
                s += pptoken::str();
                for (ptr<pptoken> token : m_attrs) {
                    s += ", ";
                    s += token->str();
                }
                s += ")";
                return s;
            }
            
        private:
            ptr<bsp_barren> m_parent;
            list<ptr<pptoken>> m_attrs;
        };
        
    }
}

#endif /* bsp_barren_h */
