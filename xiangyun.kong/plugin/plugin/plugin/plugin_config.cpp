//
//  plugin_plugin_config.cpp
//  plugin
//
//  Created by 孔祥云 on 10/16/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include "plugin_config.hpp"

#include <class_names.hpp>
#include <config_keys.hpp>

namespace pf {
    
    plugin_config::plugin_config(xml_node<>* xml) {
        m_xml = xml;
    }
    
    xml_node<>* plugin_config::get_private_param() const {
        return m_xml->first_node(CFG_PRIVATE_PARAM.c_str());
    }
    
    string plugin_config::get_lib_path() const {
        xml_attribute<>* attr = m_xml->first_attribute(CFG_LIB_PATH.c_str());
        if(attr != nullptr)
            return attr->value();
        else
            return "";
    }
    
    string plugin_config::get_name() const {
        xml_attribute<>* attr = m_xml->first_attribute(CFG_PLUGIN_NAME.c_str());
        if(attr != nullptr)
            return attr->value();
        else
            return "";
    }
    
    string plugin_config::get_init_func() const {
        xml_attribute<>* attr = m_xml->first_attribute(CFG_INIT_FUNC.c_str());
        if(attr != nullptr)
            return attr->value();
        else
            return "";
    }
}
