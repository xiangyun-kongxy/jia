//
// Created by 孔祥云 on 8/2/16.
//

#include "common_event.h"
#include <identifier/id_any.h>
#include <identifier/id_name.h>
#include <plugin/plugin.h>

using namespace kxy;

namespace plugin {

    common_event::common_event(const string &name, ptr<identifier> dst, ptr<data> param) {
        m_event_name = name;
        m_dst = dst;
        m_param = param;

        m_deliver = get_this_plugin();
    }

    common_event::common_event(const string& name, const string& dst, ptr<data> param) {
        m_param = param;
        m_event_name = name;
        m_dst = (identifier*)new id_name(dst);
        m_deliver = get_this_plugin();
    }

    common_event::common_event(const string& name, ptr<data> param) {
        
        m_param = param;
        m_event_name = name;
        m_deliver = get_this_plugin();

        m_dst = (identifier*)new id_any();
    }
    
    common_event::~common_event() {
        
    }

    string common_event::type() const {
        return typeid(common_event).name();
    }

    ptr<plugin> common_event::deliver() const {
        return m_deliver;
    }

    ptr<identifier> common_event::destination() const {
        return m_dst;
    }

    const string &common_event::event_type() const {
        return m_event_name;
    }

    ptr<data> common_event::param() const {
        return m_param;
    }

    bool common_event::is_kind_of(const string &type_name) const {
        return type_name == type() || event::is_kind_of(type_name);
    }
}

