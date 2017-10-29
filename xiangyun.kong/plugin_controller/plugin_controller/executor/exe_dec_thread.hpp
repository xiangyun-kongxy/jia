//
//  exe_dec_thread.hpp
//  plugin_controller
//
//  Created by 孔祥云 on 10/29/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_dec_thread_h
#define exe_dec_thread_h

#include <plugin/executor/executor.hpp>
#include <plugin/manager/plugin_manager.hpp>

#include <lib/identifier/id_name.hpp>

#include <log.hpp>

namespace pf {
    
    class dec_thread : public executor {
    public:
        DECLARE_TYPE(executor, EXE_DEC_THREAD);
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            string plugin_name;
            evt->param() >> plugin_name;
            
            plugin_manager* pm = plugin_manager::instance();
            ptr<plugin> pl = pm->find_plugin(new id_name(plugin_name));
            
            if (pl != nullptr) {
                pl->dec_thread();
                info_log("info", plugin_name + " thread decreased.");
            } else {
                error_log("error", plugin_name + " not found when try to "
                          "decrease thread.");
            }
            
            return nullptr;
        }
    };
    
}

#endif /* exe_dec_thread_h */
