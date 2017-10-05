//
//  cache.cpp
//  barren_cache
//
//  Created by 孔祥云 on 1/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "cache.hpp"
#include <math.h>

namespace mind {
    
    cache::cache(long capacity) {
        m_capacity = capacity;
        m_frequent = 1;
    }
    
    void cache::put(ptr<barren> value) {
        ++m_frequent;
        
        m_values[value->id()] = new value_info(m_frequent, value);
    }
    
    ptr<barren> cache::get(long id) {
        ++m_frequent;
        
        value_info* value = m_values[id];
        if(value != nullptr) {
            value->update_frequent(m_frequent, m_values.size(), m_capacity);
            return value->value;
        } else {
            return nullptr;
        }
    }
    
    void cache::cleanup() {
        map<long, value_info*>::iterator i;
        for(i = m_values.begin(); i != m_values.end();) {
            if(i->second->expired(m_frequent, m_values.size(), m_capacity)) {
                delete i->second;
                m_values.erase(i++);
            } else {
                ++i;
            }
        }
    }
    
    void cache::value_info::update_frequent(long seed, long size, long capacity) {
        frequent += (seed - frequent) * (capacity + size) / (3.0 * capacity);
    }
    
    bool cache::value_info::expired(long seed, long size, long capacity) {
        double distance = (seed - frequent) / (double)size;
        return distance > capacity / (double)size;
    }
}
