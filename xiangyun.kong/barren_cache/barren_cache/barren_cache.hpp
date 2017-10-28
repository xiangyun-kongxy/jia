//
//  barren_cache.hpp
//  barren_cache
//
//  Created by 孔祥云 on 1/13/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef barren_cache_hpp
#define barren_cache_hpp

#include <lib/identifier/id_name.hpp>

#include <plugin/plugin/plugin.hpp>

#include <barren_cache/cache/cache.hpp>

#include <messages.hpp>

using namespace pf;

namespace mind {
    
    class barren_cache : public plugin {
    public:
        barren_cache();
        DECLARE_TYPE(plugin, PLUGIN_BARREN_CACHE);
        
    public:
        ptr<barren> load_barren(long id);
        void save_barren(ptr<barren> obj);

    public:
        virtual list<ptr<identifier>> depend_on() const override {
            list<ptr<identifier>> dependence;
            dependence.push_back(new id_name(M_SAVE_BARREN));
            dependence.push_back(new id_name(M_LOAD_BARREN));
            
            return dependence;
        }
        
    private:
        ptr<barren> load_barren_from_memory(long id);
        void save_barren_to_memory(ptr<barren> obj);
       
    private:
        ptr<identifier> m_provider;
        cache* m_cache;
    };
    
}

#endif /* barren_cache_hpp */
