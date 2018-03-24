//
//  participle.hpp
//  gower
//
//  Created by 孔祥云 on 3/10/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef participle_hpp
#define participle_hpp

#include <stdio.h>

#include "trie.hpp"


namespace mind{
    
    class participle {
    public:
        participle(const string& text);
        
    public:
        list<long> get_next();
        
    private:
        void _part(list<part_attr*>& cur, const char* str, long& pos);
        long _envalue(const list<part_attr*>& part);
        
    private:
        string m_text;
        list<pair<long, list<part_attr*>>> m_parting;
        long m_next_get_pos;
    };
    
}

#endif /* participle_hpp */
