//
//  id_simple_event.hpp
//  common
//
//  Created by xiangyun.kong on 10/16/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef id_simple_event_h
#define id_simple_event_h

#include <lib/identifier/identifier.hpp>

#include <plugin/event/simple_event.hpp>

using namespace pf;

namespace kxy {


    class id_simple_event : public identifier {
    public:
        DECLARE_TYPE(identifier, ID_SIMPLE_EVENT);
        
    public:
        id_simple_event(const string& evt, ptr<identifier> base = nullptr)
        :   identifier(base),
        m_evt(evt) {
        }

    public:
        virtual bool match(ptr<object> obj) override {
            if (obj->is_kind_of(OBJ_EVENT)) {
                return m_evt == obj->name()
                && identifier::match(obj);
            }
            return false;
        }

    protected:
        string m_evt;
    };
    
}

#endif /* id_simple_event_h */
