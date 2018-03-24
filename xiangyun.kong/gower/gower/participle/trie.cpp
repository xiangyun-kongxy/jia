//
//  trie.cpp
//  gower
//
//  Created by 孔祥云 on 3/17/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "trie.hpp"

#include <ipc.hpp>
#include <messages.hpp>

#include <lib/identifier/id_name.hpp>

using namespace kxy;
using namespace pf;

namespace mind {
    
    ptr<id_name> g_cfg_provider = new id_name(PLUGIN_CONFIG_CENTER);
    
    trie::trie() {
        part_attr* attr;
        
        ptr<serializable> rsp;
        long index = 0;
        
        do {
            rsp = call_plugin(g_cfg_provider,
                              M_GET_CONFIG, PLUGIN_GOWER, l2s(index));
            if (rsp != nullptr) {
                ++index;
                attr = new part_attr;
                rsp >> *attr;
                put(attr->str().c_str(), attr);
            }
        } while (rsp != nullptr);
    }
    
    trie::~trie() {
        _save_erase(m_root, 0);
        m_root = nullptr;
    }
    
    void trie::put(const char *str, part_attr *attr) {
        node* cur = m_root;
        long pos = 0;
        cur = _find(cur, str, pos);
        
        node* n;
        while (str[pos] != 0) {
            n = new node;
            cur->transfer[(unsigned char)str[pos]] = n;
            cur = n;
        }
        
        if (cur->attr != nullptr) {
            delete cur->attr;
        }
        cur->attr = attr;
    }
    
    list<part_attr*> trie::match(const char *str) {
        list<part_attr*> result;
        
        long pos = 0;
        node* next = m_root;
        node* cur;
        do {
            cur = next;
            if (cur->attr != nullptr) {
                result.push_back(cur->attr);
            }
            next = _find(cur, str, pos);
        } while (next != cur);
        
        return result;
    }
    
    part_attr* trie::match_shortest(const char *str) {
        long pos = 0;
        node* cur = _find(m_root, str, pos);
        
        return cur->attr;
    }
    
    part_attr* trie::match_longest(const char *str) {
        long pos = 0;
        node* next = m_root;
        node* cur;
        do {
            cur = next;
            next = _find(cur, str, pos);
        } while (next != cur);
        
        return cur->attr;
    }
    
    part_attr* trie::match_with_attr(const char *str, part_attr *attr,
                                     bool (*matcher)(part_attr*, part_attr*)) {
         long pos = 0;
         node* next = m_root;
         node* cur;
         do {
             cur = next;
             if ((*matcher)(attr, cur->attr)) {
                 return cur->attr;
             }
             next = _find(cur, str, pos);
         } while (next != cur);
         
         return nullptr;
     }
    
    trie::node* trie::_find(trie::node *cur, const char *str, long &pos) {
        long p = pos;
        
        trie::node* n;
        while (str[p] != 0) {
            n = cur->transfer[(unsigned char)str[p]];
            if (n != nullptr) {
                ++p;
                cur = n;
                if (cur->attr != nullptr) {
                    break;
                }
            }
        }
        
        pos = p;
        return cur;
    }
    
    void trie::_save_erase(trie::node *root, long index) {
        if (root->attr != nullptr) {
            ptr<serializable> sa = new serializable;
            sa << *root->attr;
            call_plugin(g_cfg_provider,
                        M_PUT_CONFIG, PLUGIN_GOWER, l2s(index), sa->buf());
            ++index;
            delete root->attr;
            root->attr = nullptr;
        }
        
        for (long i = 0; i < 256; ++i) {
            if (root->transfer[i] != nullptr) {
                _save_erase(root->transfer[i], index);
            }
        }
        
        delete root;
    }
}
