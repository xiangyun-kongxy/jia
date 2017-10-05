//
// Created by 孔祥云 on 7/30/16.
//

#ifndef PLUGIN_RESPONSE_H
#define PLUGIN_RESPONSE_H

#include <object/object.h>
#include <object/ptr.h>
#include <serialize/serializable.hpp>

using namespace kxy;

namespace pf {

    class response : public object {
    public:
        virtual long code() = 0;
        virtual string message() = 0;
        virtual ptr<serializable> context() = 0;

        virtual string type() const override {
            return "response";
        }
       
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "response" || object::is_kind_of(type_name);
        }

    };

}

#endif //PLUGIN_RESPONSE_H
