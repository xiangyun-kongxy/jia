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

#include <messages.hpp>

using namespace pf;

namespace kxy {
    
    class config_center : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_CONFIG_CENTER);
        
        IMPL_BEGIN
        IMPL_F(T_STR, M_GET_CONFIG, T_STR)
        IMPL_F(T_NONE, M_PUT_CONFIG, T_STR, T_STR)
        IMPL_END
        
    public:
        config_center();
        
    public:
        string get(const string& key);
        void put(const string& key, const string& value);
        
    private:
        static const string m_service;
    };
}

#endif /* config_center_hpp */
