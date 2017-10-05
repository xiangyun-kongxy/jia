//
//  exe_on_get_config.h
//  config_center
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_on_get_config_h
#define exe_on_get_config_h

#include <executor/executor.h>
#include <response/simple_response.h>
#include <constants.h>
#include "../config_center.hpp"
#include "../config_functions.h"

using namespace pf;

namespace kxy {
    
    class exe_on_get_config : public executor {
    public:
        virtual ptr<response> run(ptr<plugin> plugin, ptr<task> task) override {
            ptr<config_center> owner = plugin;
            ptr<serializable> data = task->param();
            string key;
            data >> key;
            string config = owner->get(key);
            data << config;
            return new simple_response(EC_OK, EM_OK, data);
        }
        
        virtual string type() const override {
            return "exe_on_get_config";
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "exe_on_get_config" || executor::is_kind_of(type_name);
        }
    };
    
}

#endif /* exe_on_get_config_h */
