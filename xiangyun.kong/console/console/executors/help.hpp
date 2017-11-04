//
//  help.hpp
//  console
//
//  Created by 孔祥云 on 11/4/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef help_h
#define help_h

#include <console/terminal.hpp>

namespace pf {
    
    class help : public executor {
    public:
        DECLARE_TYPE(executor, "exe_help");
        
    public:
        ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<terminal> term = owner;
            
            cout << "commands:" << endl;
            
            list<ptr<plugin>> plugins;
            plugins = plugin_manager::instance()->get_all_plugin();
            for (ptr<plugin> pl : plugins) {
                for (ptr<pf::function> func : pl->supported_functions()) {
                    printf("    @%-16s:%-20s ", func->provider()->name().c_str(),
                           func->name().c_str());
                    for (TYPE ty : func->param_type()) {
                        switch (ty) {
                            case pf::T_NONE:
                                printf (" %-7s", "-");
                                break;
                            case pf::T_INT:
                                printf (" %-7s", "integer");
                                break;
                            case pf::T_STR:
                                printf (" %-7s", "string");
                                break;
                            case pf::T_FLOAT:
                                printf (" %-7s", "float");
                                break;
                            case pf::T_USER:
                                printf (" %-7s", "*");
                                break;
                        }
                    }
                    cout << endl;
                }
            }
            
            return nullptr;
        }
    };
    
}

#endif /* help_h */
