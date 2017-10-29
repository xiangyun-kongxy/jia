//
//  id_response.hpp
//  common
//
//  Created by xiangyun.kong on 10/28/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef id_response_h
#define id_response_h

#include <lib/identifier/identifier.hpp>

#include <plugin/response/response.hpp>

using namespace pf;

namespace kxy {


    class id_response : public identifier {
    public:
        DECLARE_TYPE(identifier, ID_TASK_RESPONSE);

    public:
        id_response(ptr<event> evt, ptr<identifier> base = nullptr)
        :   identifier(base),
        m_evt(evt) {
        }

    public:
        virtual bool match(ptr<object> obj) override {
            if (obj->is_kind_of(OBJ_RESPONSE)) {
                return m_evt == ((ptr<response>)obj)->org_event()
                && identifier::match(obj);
            }
            return false;
        }

    public:
        ptr<object> event() const {
            return m_evt;
        }

    protected:
        ptr<object> m_evt;
    };
    
}

#endif /* id_response_h */
