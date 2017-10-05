//
// Created by xiangyun.kong on 8/8/16.
//

#include "simple_response.h"

namespace plugin {

    simple_response::simple_response(long code, const string& msg, ptr<data> context) {
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

    ptr<data> simple_response::context() {
        return m_context;
    }

    string simple_response::type() const {
        return typeid(simple_response).name();
    }

    bool simple_response::is_kind_of(const string &type_name) const {
        return type_name == type() || response::is_kind_of(type_name);
    }
}
