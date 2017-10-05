//
//  loader.cpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include "loader.hpp"
#include <fs/file_util.h>
#include <dlfcn.h>
#include "../lifecycle_function.h"

using namespace kxy;
using namespace rapidxml;

namespace pf {
    
    list<config*> loader::read_config_file(const string &path) {
        string conf = file_util::read(path);
        char* buf = new char[conf.length() + 1];
        strcpy(buf, conf.c_str());
        
        list<config*> confs;
        
        xml_document<> doc;
        doc.parse<0>(buf);
        xml_node<>* root = doc.first_node();
        if(root != nullptr) {
            xml_node<>* child = root->first_node(CFG_PLUGIN.c_str());
            while(child != nullptr) {
                confs.push_back(new config(child));
                child = child->next_sibling(CFG_PLUGIN.c_str());
            }
        }
        return confs;
    }
    
    ptr<plugin> loader::load_plugin(const config *conf) {
        string lib_path = conf->get_lib_path();
        string init_func_name = conf->get_init_func();

        void* lib = dlopen(lib_path.c_str(), RTLD_NOW);
        void* init_func = dlsym(lib, init_func_name.c_str());
        
        return ((plugin_init_func)init_func)(conf->get_private_param());
    }
    
}
