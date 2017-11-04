//
//  run_cmd.hpp
//  console
//
//  Created by 孔祥云 on 11/4/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef run_cmd_h
#define run_cmd_h

#include <console/terminal.hpp>

namespace pf {
    
    class run_cmd : public executor {
    public:
        DECLARE_TYPE(executor, "exe_runcmd");
        
    public:
        ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<terminal> term = owner;
            list<string> cmds;
            evt->param() >> cmds;
            
            term->call_function(cmds);
            return nullptr;
        }
    };
            
}
            
#endif /* run_cmd_h */
