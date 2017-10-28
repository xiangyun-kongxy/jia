//
// Created by 孔祥云 on 8/9/16.
//

#ifndef PLUGIN_EXECUTOR_H
#define PLUGIN_EXECUTOR_H

#include <lib/object/object.hpp>
#include <lib/object/ptr.hpp>

#include <plugin/response/response.hpp>
#include <plugin/event/event.hpp>

namespace pf {
    
    class executor : public object {
    public:
        DECLARE_TYPE(object, OBJ_EXECUTOR);
        
    public:
        virtual ptr<response> run(ptr<plugin>, ptr<event>) = 0;

    };

}

#endif //PLUGIN_EXECUTOR_H
