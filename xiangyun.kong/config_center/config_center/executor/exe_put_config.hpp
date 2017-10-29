//
//  exe_on_put_config.h
//  config_center
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_on_put_config_h
#define exe_on_put_config_h

#include <config_center/config_center.hpp>

using namespace pf;

namespace kxy {
    
    class put_config : public executor {
    public:
        DECLARE_TYPE(executor, EXE_PUT_CONFIG);

    public:
        virtual ptr<response> run(ptr<plugin> plugin,ptr<event> event) override {
            ptr<config_center> owner = plugin;
            ptr<serializable> data = event->param();
            string key;
            string config;
            data >> key >> config;
            owner->put(key, config);

            return nullptr;
        }
        
    };
    
}

#endif /* exe_on_put_config_h */
