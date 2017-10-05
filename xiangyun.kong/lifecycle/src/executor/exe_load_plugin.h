//
//  exe_load_plugin.h
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef exe_load_plugin_h
#define exe_load_plugin_h

#include <include/constants.h>
#include <response/simple_response.h>
#include <executor/executor.h>
#include <plugin/config.hpp>
#include <manager/plugin_manager.hpp>
#include "../load/loader.hpp"
#include "../lifecycle_function.h"

namespace pf {
    
    class exe_load_plugin : public executor {
    public:
        
        virtual ptr<response> run(ptr<plugin> owner, ptr<task> msg) override {
            ptr<serializable> data = msg->param();
            string path;
            data >> path;
            
            // TODO: use load steps
            list<config*> confs = loader::read_config_file(path);
            list<config*>::const_iterator i;
            for(i = confs.begin(); i != confs.end(); ++i) {
                ptr<plugin> instance = loader::load_plugin(*i);
                if(instance != nullptr) {
                    plugin_manager::instance()->add_plugin(instance);
                }
            }
            
            // TODO: return load result;
            return new simple_response(EC_OK, EM_OK);
        }
        
        virtual string type() const override {
            return "exe_load_plugin";
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "exe_load_plugin" || object::is_kind_of(type_name);
        }
    };
    
}

#endif /* exe_load_plugin_h */
