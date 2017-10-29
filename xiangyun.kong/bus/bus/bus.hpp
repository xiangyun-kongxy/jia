//
// Created by 孔祥云 on 8/10/16.
//

#ifndef PLUGIN_BUS_H
#define PLUGIN_BUS_H

#include <plugin/plugin/plugin.hpp>

#include <bus/executor/exe_on_route.hpp>

namespace pf {
    
    class bus : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_BUS);
        
        IMPL_BEGIN
        IMPL_END
        
    public:
        bus();
        
    public:
        virtual ptr<response> do_task(ptr<event> evt) override;

    public:
        ptr<on_route> m_router;
    };
    
}

#endif //PLUGIN_BUS_H
