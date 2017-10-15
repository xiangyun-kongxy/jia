//
//  memory.hpp
//  memory
//
//  Created by 孔祥云 on 1/7/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef memory_hpp
#define memory_hpp

#include <plugin/plugin.h>
#include <object/ptr.h>
#include <barren/barren.hpp>

using namespace pf;
using namespace kxy;

namespace mind {
    
    class memory : public plugin {
    public:
        memory();
        
    public:
        virtual string type() const override ;
        virtual bool is_kind_of(const string &type_name) const override ;
        
    public:
        void write(ptr<barren> obj);
        ptr<barren> read(long id);
        
    private:
        static const string m_path;
    };
    
}

#endif /* memory_hpp */
