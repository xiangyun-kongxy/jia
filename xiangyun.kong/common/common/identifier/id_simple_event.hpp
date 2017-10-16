//
//  id_simple_event.hpp
//  common
//
//  Created by xiangyun.kong on 10/16/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef id_simple_event_h
#define id_simple_event_h

#include <identifier/identifier.h>
#include <event/simple_event.h>
#include <names.h>

using namespace pf;

namespace kxy {


    class id_simple_event : public identifier {
    public:
        id_simple_event(const string& evt, ptr<identifier> base = nullptr)
        :   identifier(base),
        m_evt(evt) {
        }

    public:
        virtual bool match(ptr<object> obj) override {
            if (obj->is_kind_of(OBJ_EVENT)) {
                return m_evt == ((ptr<simple_event>)obj)->event_type()
                && identifier::match(obj);
            }
            return false;
        }

        virtual string type() const override {
            return ID_SIMPLE_EVENT;
        }

        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == ID_SIMPLE_EVENT
            || identifier::is_kind_of(type_name);
        }

    protected:
        string m_evt;
    };
    
}

#endif /* id_simple_event_h */
