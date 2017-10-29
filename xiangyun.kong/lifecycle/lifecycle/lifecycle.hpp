//
//  lifecycle.hpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef lifecycle_hpp
#define lifecycle_hpp

#include <plugin/plugin/plugin.hpp>
#include <plugin/plugin/plugin_config.hpp>

namespace pf {


    
    class lifecycle : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_LIFECYCLE);
        
        IMPL_BEGIN
        IMPL_END
        
    public:
        lifecycle();
        virtual ~lifecycle();

    public:
        virtual void init() override;

    public:
        void set_config(char* buf, const list<plugin_config*>& configs);

    private:
        map<char*, list<plugin_config*>> m_configs;
    };
    
}

#endif /* lifecycle_hpp */
