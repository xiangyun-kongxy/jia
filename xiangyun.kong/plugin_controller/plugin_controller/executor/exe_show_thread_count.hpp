//
//  exe_show_thread_count.hpp
//  plugin_controller
//
//  Created by 孔祥云 on 11/4/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_show_thread_count_h
#define exe_show_thread_count_h

#include <plugin/executor/executor.hpp>
#include <plugin/response/simple_response.hpp>
#include <plugin/manager/plugin_manager.hpp>

#include <lib/identifier/id_name.hpp>

#include <log.hpp>
#include <errors.hpp>

namespace pf {
    
    class show_thread_count : public executor {
    public:
        DECLARE_TYPE(executor, EXE_SHOW_THREAD_COUNT);
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            string plugin_name;
            evt->param() >> plugin_name;
            
            plugin_manager* pm = plugin_manager::instance();
            ptr<plugin> pl = pm->find_plugin(new id_name(plugin_name));
            
            
            ptr<response> rsp;
            
            if (pl != nullptr) {
                ptr<serializable> result = new serializable;
                result << pl->thread_count();
                rsp = new simple_response(evt, EC_OK, EM_OK, result);
            } else {
                rsp  = new simple_response(evt, EC_PLUGIN_NOT_FOUND,
                                           EM_PLUGIN_NOT_FOUND);
            }
            
            return rsp;
        }
    };
            
}

#endif /* exe_show_thread_count_h */
