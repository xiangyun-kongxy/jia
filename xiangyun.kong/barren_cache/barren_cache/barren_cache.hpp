//
//  barren_cache.hpp
//  barren_cache
//
//  Created by 孔祥云 on 1/13/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef barren_cache_hpp
#define barren_cache_hpp

#include <plugin/plugin.h>
#include "cache/cache.hpp"

using namespace pf;

namespace mind {
    
    class barren_cache : public plugin {
    public:
        barren_cache();
        
    public:
        ptr<barren> get_barren(long id);
        void put_barren(ptr<barren> obj);
        
    public:
        virtual string type() const override;
        virtual bool is_kind_of(const string &type_name) const override ;
        
    private:
        ptr<barren> load_barren(long id);
        void save_barren(ptr<barren> obj);
       
    private:
        ptr<identifier> m_provider;
        cache* m_cache;
    };
    
}

#endif /* barren_cache_hpp */
