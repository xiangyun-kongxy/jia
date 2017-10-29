//
//  exe_show_task_count.hpp
//  plugin_controller
//
//  Created by 孔祥云 on 10/29/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_show_task_count_h
#define exe_show_task_count_h

#include <plugin/executor/executor.hpp>
#include <plugin/response/simple_response.hpp>
#include <plugin/manager/plugin_manager.hpp>

#include <lib/identifier/id_name.hpp>

#include <log.hpp>
#include <errors.hpp>

namespace pf {
    
    class show_task_count : public executor {
    public:
        DECLARE_TYPE(executor, EXE_SHOW_TASK_COUNT);
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            string plugin_name;
            evt->param() >> plugin_name;
            
            plugin_manager* pm = plugin_manager::instance();
            ptr<plugin> pl = pm->find_plugin(new id_name(plugin_name));
            
            ptr<response> rsp;
            if (pl != nullptr) {
                long count = pl->tasks()->size();
                ptr<serializable> result = new serializable;
                result << count;
                rsp = new simple_response(evt, EC_OK, EM_OK, result);
                
                info_log("info", plugin_name + " task count got: " +
                         to_string(count));
            } else {
                rsp = new simple_response(evt, EC_PLUGIN_NOT_FOUND,
                                          EM_PLUGIN_NOT_FOUND);
                
                error_log("error", plugin_name + " not found when try to "
                          "get task count.");
            }
            
            return rsp;
        }
    };
    
}

#endif /* exe_show_task_count_h */
