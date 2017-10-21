//
//  cache.hpp
//  barren_cache
//
//  Created by 孔祥云 on 1/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef cache_hpp
#define cache_hpp

#include <map>
#include <string>

#include <lib/object/ptr.h>
#include <barren/barren.hpp>

using namespace std;

namespace mind {
    
    class cache {
    public:
        cache(long capacity);
        
    public:
        void put(ptr<barren> value);
        ptr<barren> get(long id);
        
        void cleanup();
        
    private:
        struct value_info {
            long frequent;
            ptr<barren> value;
            
            value_info(long freq, ptr<barren> val) {
                frequent = freq;
                value = val;
            }
            
            void update_frequent(long seed, long size, long capacity);
            bool expired(long seed, long size, long capacity);
        };
        
    private:
        map<long, value_info*> m_values;
        long m_frequent;
        long m_capacity;
        mutex m_mutex;
    };
    
}

#endif /* cache_hpp */
