//
//  loader.cpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include "loader.hpp"

#include <dlfcn.h>

#include <lib/fs/file_util.hpp>

#include <class_names.hpp>
#include <config_keys.hpp>

#include <log.hpp>

using namespace kxy;
using namespace rapidxml;

namespace pf {
    
    list<plugin_config*> plugin_loader::read_config_file(const string &path, char*& buf) {
        list<plugin_config*> confs;

        string conf = file_util::read(path);
        buf = new char[conf.length() + 1];
        strcpy(buf, conf.c_str());
        
        xml_document<> doc;
        doc.parse<0>(buf);
        xml_node<>* root = doc.first_node();
        if(root != nullptr) {
            xml_node<>* child = root->first_node(CFG_PLUGIN.c_str());
            while(child != nullptr) {
                confs.push_back(new plugin_config(child));
                child = child->next_sibling(CFG_PLUGIN.c_str());
            }
        }
        
        return confs;
    }
    
    ptr<plugin> plugin_loader::load_plugin(const plugin_config *conf) {
        string lib_path = conf->get_lib_path();
        string init_func_name = conf->get_init_func();

        void* lib = dlopen(lib_path.c_str(), RTLD_NOW);
        if (lib != nullptr) {
            void* init_func = dlsym(lib, init_func_name.c_str());
            if (init_func != nullptr) {
                return ((plugin_init_func)init_func)(conf->get_private_param());
            } else {
                error_log("error", init_func_name + ": " + dlerror());
            }
        } else {
            error_log("error", lib_path + ": " + dlerror());
        }
        return nullptr;
    }
    
}
