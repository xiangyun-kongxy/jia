//
//  id_task_response.hpp
//  lib
//
//  Created by xiangyun.kong on 10/16/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef id_task_response_h
#define id_task_response_h


#include <lib/identifier/identifier.h>

#include <plugin/task/task.h>
#include <plugin/response/response.h>

#include <names.h>

using namespace pf;

namespace kxy {


    class id_task_response : public identifier {
    public:
        DECLARE_TYPE(identifier, ID_TASK_RESPONSE);
        
    public:
        id_task_response(ptr<task> tsk, ptr<identifier> base = nullptr)
        :   identifier(base),
            m_tsk(tsk) {
        }

    public:
        virtual bool match(ptr<object> obj) override {
            if (obj->is_kind_of(OBJ_RESPONSE)) {
                return m_tsk == ((ptr<response>)obj)->org_task()
                && identifier::match(obj);
            }
            return false;
        }

    protected:
        ptr<task> m_tsk;
    };

}

#endif /* id_task_response_h */
