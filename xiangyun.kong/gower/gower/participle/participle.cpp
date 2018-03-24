//
//  participle.cpp
//  gower
//
//  Created by 孔祥云 on 3/10/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "participle.hpp"

namespace mind {
    
    extern trie* g_part_knowledge;
    
    participle::participle(const string& text) {
        m_text = text;
        m_next_get_pos = 0;
        
        long pos = 0;
        list<part_attr*> holder;
        _part(holder, text.c_str(), pos);
    }
    
    list<long> participle::get_next() {
        list<pair<long,list<part_attr*>>>::iterator it = m_parting.begin();
        for (long i = 0; i < m_next_get_pos; ++i) {
            if (it != m_parting.end()) {
                ++it;
            } else {
                return list<long>();
            }
        }
        ++ m_next_get_pos;
        
        list<long> result;
        for (part_attr* attr : (*it).second) {
            ++ attr->frequence();
            result.push_back(attr->barren());
        }
        
        if (it != m_parting.begin()) {
            --it;
            for (part_attr* attr : (*it).second) {
                -- attr->frequence();
            }
        }
        
        return result;
    }
    
    void participle::_part(list<part_attr *> &cur, const char *str, long &pos) {
        if (str[pos] == 0) {
            long value = _envalue(cur);
            
            list<pair<long,list<part_attr*>>>::iterator i = m_parting.begin();
            while (i != m_parting.end() && (*i).first > value) {
                ++i;
            }
            
            if (i != m_parting.begin()) {
                --i;
            }
            m_parting.insert(i, pair<long, list<part_attr*>>(value, cur));
        } else {
            list<part_attr*> ps = g_part_knowledge->match(str + pos);
            
            if (ps.empty()) {
                ++pos;
                _part(cur, str, pos);
            } else {
                for (part_attr* pa : ps) {
                    cur.push_back(pa);
                    pos += pa->str().length();
                    
                    _part(cur, str, pos);
                    
                    pos -= pa->str().length();
                    cur.pop_back();
                }
            }
        }
    }
    
    long participle::_envalue(const list<mind::part_attr *> &part) {
        long sum = 0;
        for (part_attr* attr : part) {
            sum += attr->frequence();
        }
        
        long avg = sum / part.size();
        
        long variance = 0;
        for (part_attr* attr : part) {
            variance += (attr->frequence() - avg) * (attr->frequence() - avg);
        }
        
        return - variance / part.size();
    }
}
