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

#include <plugin/plugin/plugin.hpp>

#include <mutex>

using namespace kxy;
using namespace std;

namespace pf {



    class function_manager {
    private:
        friend class plugin_manager;
        friend void __init_function_manager();
        friend void __uninit_function_manager();
        function_manager();
        ~function_manager();
        
    public:
        static function_manager* instance();
        bool is_actived(ptr<identifier> id);

    private:
        void add_function(ptr<plugin> owner, ptr<function> func);
        void rm_function(ptr<function> func);
        void active_function(ptr<function> func);
        void suspend_function(ptr<function> func);

    private:
        
        struct function_info {
            ptr<function> func;
            bool is_active;
            ptr<plugin> provider;

            bool operator == (const ptr<function>& func) {
                return this->func->name() == func->name() &&
                    this->func->provider() == func->provider();
            }
            
            bool operator == (const ptr<identifier>& id) {
                return id->match(func);
            }
        };
        
        list<function_info> m_functions;
        
    };
    
}

#endif /* function_manager_hpp */
