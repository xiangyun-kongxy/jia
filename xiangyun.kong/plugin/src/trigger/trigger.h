//
// Created by 孔祥云 on 8/9/16.
//

#ifndef PLUGIN_TRIGGER_H
#define PLUGIN_TRIGGER_H

#include <object/object.h>
#include <object/ptr.h>
#include <event/event.h>

using namespace kxy;
namespace pf {

    class trigger : public object {
    public:
        virtual void occur(ptr<plugin>,ptr<event>) = 0;

        virtual string type() const override {
            return "trigger";
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "trigger" || object::is_kind_of(type_name);
        }

    };

}

#endif //PLUGIN_TRIGGER_H
