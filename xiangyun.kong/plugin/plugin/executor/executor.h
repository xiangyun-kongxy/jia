//
// Created by 孔祥云 on 8/9/16.
//

#ifndef PLUGIN_EXECUTOR_H
#define PLUGIN_EXECUTOR_H

#include <lib/object/object.h>
#include <lib/object/ptr.h>

#include <plugin/response/response.h>
#include <plugin/task/task.h>

namespace pf {
    
    class executor : public object {
    public:
        DECLARE_TYPE(object, OBJ_EXECUTOR);
        
    public:
        virtual ptr<response> run(ptr<plugin>, ptr<task>) = 0;

    };

}

#endif //PLUGIN_EXECUTOR_H
