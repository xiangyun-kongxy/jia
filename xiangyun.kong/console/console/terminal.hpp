//
//  termial.hpp
//  console
//
//  Created by 孔祥云 on 11/4/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef termial_hpp
#define termial_hpp

#include <plugin/plugin/plugin.hpp>

namespace pf {
    
    class terminal : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_TERMINAL);
        
        IMPL_BEGIN
        IMPL_F(T_NONE, "?")
        IMPL_F(T_NONE, "h")
        IMPL_F(T_NONE, "H")
        IMPL_F(T_NONE, "help")
        IMPL_F(T_NONE, "Help")
        IMPL_F(T_NONE, "start", T_STR);
        IMPL_F(T_NONE, "stop");
        IMPL_F(T_NONE, "exit");
        IMPL_END
        
    public:
        terminal();
        
    public:
        ptr<response> do_task(ptr<event> evt) override;
        
    public:
        void command_loop();
        string& operator [] (const string& key);
        void call_function(list<string> cmds);
        
    private:
        list<string> _get_cmd();
        void _update_functions();
        
    private:
        map<string, list<ptr<pf::function>>> m_functions;
        map<string, string> m_status;
    };
}

#endif /* termial_hpp */
