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
#include <fs/xml.h>
using namespace rapidxml;
using namespace std;

namespace pf {
    
    class config {
    public:
        config(xml_node<> *xml);
        
    public:
        xml_node<>* get_private_param() const;
        
        string get_lib_path() const;
        string get_plugin_name() const;
        string get_init_func() const;
        
    private:
        xml_node<>* m_xml;
    };
}

#endif /* plugin_config_hpp */
