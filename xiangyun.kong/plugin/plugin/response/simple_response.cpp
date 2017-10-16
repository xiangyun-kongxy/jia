//
// Created by xiangyun.kong on 8/8/16.
//

#include "simple_response.h"

namespace pf {

    simple_response::simple_response(ptr<task> tsk, long code,
                                     const string& msg,
                                     ptr<serializable> context)
    : response(tsk) {
        m_code = code;
        m_msg = msg;
        m_context = context;
    }

    long simple_response::code() {
        return m_code;
    }

    string simple_response::message() {
        return m_msg;
    }

    ptr<serializable> simple_response::context() {
        return m_context;
    }

    string simple_response::type() const {
        return OBJ_SIMPLE_RESPONSE;
    }

    bool simple_response::is_kind_of(const string &type_name) const {
        return type_name == OBJ_SIMPLE_RESPONSE
        || response::is_kind_of(type_name);
    }
}
