//
// Created by 孔祥云 on 7/30/16.
//

#ifndef PLUGIN_RESPONSE_H
#define PLUGIN_RESPONSE_H

#include <lib/object/object.hpp>
#include <lib/object/ptr.hpp>
#include <lib/serialize/serializable.hpp>
#include <plugin/event/event.hpp>

using namespace kxy;

namespace pf {

    class response : public object {
    public:
        DECLARE_TYPE(object, OBJ_RESPONSE);
        
    public:
        response(ptr<event> evt) {
            m_org_event = evt;
        }

        virtual ~response() {}

    public:
        virtual long code() = 0;
        virtual string message() = 0;
        virtual ptr<serializable> context() = 0;

        ptr<event> org_event() const {
            return m_org_event;
        }
        
    protected:
        ptr<event> m_org_event;
    };

}

#endif //PLUGIN_RESPONSE_H
