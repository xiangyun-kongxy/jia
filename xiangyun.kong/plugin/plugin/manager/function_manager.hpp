//
//  function_manager.hpp
//  plugin
//
//  Created by xiangyun.kong on 10/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef function_manager_hpp
#define function_manager_hpp

#include <stdio.h>

#include <plugin/plugin/plugin.h>

using namespace kxy;

namespace pf {

    struct function_info {
        ptr<identifier> function;
        bool is_active;
        ptr<plugin> provider;

        bool operator == (const ptr<identifier>& id) {
            return id->match(function);
        }
    };

    class function_manager {
    private:
        friend void __init_function_manager();
        function_manager();
    public:
        static function_manager* instance();

    public:
        void add_function(ptr<plugin> owner, ptr<identifier> function);
        void rm_function(ptr<identifier> function);
        void active_function(ptr<identifier> function);
        void suspend_function(ptr<identifier> function);
        
        bool check_ready(ptr<identifier> id);
    private:
        list<function_info> m_functions;
        
        pthread_mutex_t m_mutex;
    };
    
}

#endif /* function_manager_hpp */
