//
//  trie.hpp
//  gower
//
//  Created by 孔祥云 on 3/17/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef trie_hpp
#define trie_hpp

#include <stdio.h>

#include "part_attr.hpp"

namespace mind {
    
    class trie {
    public:
        trie();
        ~trie();
        
    public:
        void put(const char* str, part_attr* attr);
        
        list<part_attr*> match(const char* str);
        part_attr* match_shortest(const char* str);
        part_attr* match_longest(const char* str);
        part_attr* match_with_attr(const char* str, part_attr* attr,
                                   bool (*matcher)(part_attr*, part_attr*));
        
    private:
        struct node {
            part_attr* attr;
            node* transfer[256];
            
            node() {
                attr = nullptr;
                memset(transfer, 0, 256 * sizeof(node*));
            }
        };
        
    private:
        node* _find(node* cur, const char* str, long& pos);
        void _save_erase(node* root, long index);
        
    private:
        node* m_root;
    };
    
}

#endif /* trie_hpp */
