//
//  exe_show_plugins.hpp
//  plugin_controller
//
//  Created by 孔祥云 on 10/29/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_show_plugins_h
#define exe_show_plugins_h

#include <plugin/executor/executor.hpp>
#include <plugin/response/simple_response.hpp>
#include <plugin/manager/plugin_manager.hpp>

#include <lib/identifier/id_name.hpp>

#include <log.hpp>
#include <errors.hpp>

namespace pf {
    
    class show_plugins : public executor {
    public:
        DECLARE_TYPE(executor, EXE_SHOW_PLUGINS);
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            plugin_manager* pm = plugin_manager::instance();
            list<ptr<plugin>> plugins = pm->get_all_plugin();
            
            string plugin_names;
            for (ptr<plugin> pl : plugins) {
                plugin_names += pl->name() + ",";
            }
            
            ptr<response> rsp;
            ptr<serializable> result = new serializable;
            result << plugin_names;
            rsp = new simple_response(evt, EC_OK, EM_OK, result);
                
            info_log("info", "show plugins result: " + plugin_names);
            
            return rsp;
        }
    };
            
}
                
#endif /* exe_show_plugins_h */
