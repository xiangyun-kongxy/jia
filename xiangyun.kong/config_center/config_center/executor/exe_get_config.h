//
//  exe_on_get_config.h
//  config_center
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_on_get_config_h
#define exe_on_get_config_h

#include <config_center/config_center.hpp>

#include <plugin/executor/executor.h>
#include <plugin/response/simple_response.h>

#include <errors.h>
#include <names.h>

using namespace pf;

namespace kxy {
    
    class get_config : public executor {
    public:
        virtual ptr<response> run(ptr<plugin> plugin, ptr<task> task) override {
            ptr<config_center> owner = plugin;
            ptr<serializable> data = task->param();
            string key;
            data >> key;
            data << owner->get(key);
            return new simple_response(task, EC_OK, EM_OK, data);
        }
        
        virtual string type() const override {
            return EXE_GET_CONFIG;
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == EXE_GET_CONFIG || executor::is_kind_of(type_name);
        }
    };
    
}

#endif /* exe_on_get_config_h */
