//
//  memory.hpp
//  memory
//
//  Created by 孔祥云 on 1/7/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef memory_hpp
#define memory_hpp

#include <lib/object/ptr.hpp>

#include <plugin/plugin/plugin.hpp>

#include <barren/barren.hpp>

#include <messages.hpp>

using namespace pf;
using namespace kxy;

namespace mind {
    
    class memory : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_MEMORY);
        
        IMPL_BEGIN
        IMPL_F(T_USER, M_LOAD_BARREN, T_INT)
        IMPL_F(T_NONE, M_SAVE_BARREN, T_USER)
        IMPL_END
        
    public:
        memory();
        
    public:
        void write(ptr<barren> obj);
        ptr<barren> read(long id);
        
    private:
        static const string m_path;
    };
    
}

#endif /* memory_hpp */
