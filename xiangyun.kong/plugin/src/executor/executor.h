//
// Created by 孔祥云 on 8/9/16.
//

#ifndef PLUGIN_EXECUTOR_H
#define PLUGIN_EXECUTOR_H

#include <object/object.h>
#include <response/response.h>
#include <task/task.h>
#include <object/ptr.h>

namespace pf {
    
    class executor : public object {
    public:
        virtual ptr<response> run(ptr<plugin>, ptr<task>) = 0;

        virtual string type() const override {
            return "executor";
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "executor" || object::is_kind_of(type_name);
        }

    };

}

#endif //PLUGIN_EXECUTOR_H
