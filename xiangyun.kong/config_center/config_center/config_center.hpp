//
//  config_center.hpp
//  config_center
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef config_center_hpp
#define config_center_hpp

#include <plugin/plugin/plugin.hpp>

using namespace pf;

namespace kxy {
    
    class config_center : public plugin {
    public:
        config_center();
        DECLARE_TYPE(plugin, PLUGIN_CONFIG_CENTER);
        
    public:
        string get(const string& key);
        void put(const string& key, const string& value);
        
    private:
        static const string m_service;
    };
}

#endif /* config_center_hpp */
