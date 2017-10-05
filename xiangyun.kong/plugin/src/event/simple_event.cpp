//
// Created by 孔祥云 on 8/2/16.
//

#include "simple_event.h"
#include <identifier/id_any.h>
#include <identifier/id_name.h>
#include <plugin/plugin.h>

using namespace kxy;

namespace pf {

    simple_event::simple_event(const string& name) :
    simple_event::simple_event(name, nullptr, new id_any()) {
    
    }
    
    simple_event::simple_event(const string& name, ptr<serializable> param) :
    simple_event::simple_event(name, param, new id_any()) {
    
    }
    
    simple_event::simple_event(const string& name, ptr<identifier> dst) :
    simple_event::simple_event(name, nullptr, dst) {
    
    }
    
    simple_event::simple_event(const string& name, ptr<serializable> param, ptr<identifier> dst) {
        m_deliver = plugin::current_plugin();
        m_event_name = name;
        m_param = param;
        m_dst = dst;
    }

    string simple_event::type() const {
        return "simple_event";
    }

    ptr<plugin> simple_event::deliver() const {
        return m_deliver;
    }

    ptr<identifier> simple_event::destination() const {
        return m_dst;
    }

    const string &simple_event::event_type() const {
        return m_event_name;
    }

    ptr<serializable> simple_event::param() const {
        return m_param;
    }

    bool simple_event::is_kind_of(const string &type_name) const {
        return type_name == "simple_event" || event::is_kind_of(type_name);
    }
}

