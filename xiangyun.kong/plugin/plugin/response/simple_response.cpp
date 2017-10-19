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

}
