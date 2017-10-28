//
//  plugin_config.hpp
//  plugin
//
//  Created by 孔祥云 on 10/16/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef plugin_config_hpp
#define plugin_config_hpp

#include <string>
#include <lib/fs/xml.hpp>
using namespace rapidxml;
using namespace std;

namespace pf {
    
    class plugin_config {
    public:
        plugin_config(xml_node<> *xml);
        
    public:
        xml_node<>* get_private_param() const;
        
        string get_lib_path() const;
        string get_name() const;
        string get_init_func() const;
        
    private:
        xml_node<>* m_xml;
    };
}

#endif /* plugin_config_hpp */
