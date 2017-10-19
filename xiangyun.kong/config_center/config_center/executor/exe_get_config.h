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
        DECLARE_TYPE(executor, EXE_GET_CONFIG);
        
    public:
        virtual ptr<response> run(ptr<plugin> plugin, ptr<task> task) override {
            ptr<config_center> owner = plugin;
            ptr<serializable> data = task->param();
            string key;
            data >> key;
            data << owner->get(key);
            return new simple_response(task, EC_OK, EM_OK, data);
        }
        
    };
    
}

#endif /* exe_on_get_config_h */
