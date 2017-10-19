//
// Created by 孔祥云 on 8/9/16.
//

#ifndef PLUGIN_TRIGGER_H
#define PLUGIN_TRIGGER_H

#include <lib/object/object.h>
#include <lib/object/ptr.h>
#include <plugin/event/event.h>

using namespace kxy;
namespace pf {

    class trigger : public object {
    public:
        DECLARE_TYPE(object, OBJ_TRIGGER);

    public:
        virtual void happen(ptr<plugin>,ptr<event>) = 0;

    };

}

#endif //PLUGIN_TRIGGER_H
