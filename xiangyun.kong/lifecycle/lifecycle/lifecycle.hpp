//
//  lifecycle.hpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef lifecycle_hpp
#define lifecycle_hpp

#include <plugin/plugin/plugin.h>
#include <plugin/plugin/config.hpp>

namespace pf {

    enum plugin_status {
        PS_UNKNOWN,
        PS_LOADING,
        PS_LOADED,
        PS_INSTALLING,
        PS_INSTALLED,
        PS_RUNNING,
        PS_UPGRADING,
        PS_UPGRADED,
        PS_UNINSTALLING,
        PS_UNINSTALLED,
        PS_UNLOADING,
        PS_UNLOADED,
    };
    
    class lifecycle : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_LIFECYCLE);
        
    public:
        lifecycle();
        virtual ~lifecycle();

    public:
        void set_config(char* buf, const list<config*>& configs);

    private:
        map<char*, list<config*>> m_configs;
    };
    
}

#endif /* lifecycle_hpp */
