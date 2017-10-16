//
// Created by 孔祥云 on 7/30/16.
//

#ifndef PLUGIN_RESPONSE_H
#define PLUGIN_RESPONSE_H

#include <lib/object/object.h>
#include <lib/object/ptr.h>
#include <lib/serialize/serializable.hpp>
#include <plugin/task/task.h>

using namespace kxy;

namespace pf {

    class response : public object {
    public:
        response(ptr<task> tsk) {
            m_org_task = tsk;
        }

        virtual ~response() {}

    public:
        virtual long code() = 0;
        virtual string message() = 0;
        virtual ptr<serializable> context() = 0;

        ptr<task> org_task() const {
            return m_org_task;
        }
        
        virtual string type() const override {
            return OBJ_RESPONSE;
        }
       
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == OBJ_RESPONSE || object::is_kind_of(type_name);
        }

    protected:
        ptr<task> m_org_task;
    };

}

#endif //PLUGIN_RESPONSE_H
