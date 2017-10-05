//
// Created by 孔祥云 on 8/2/16.
//

#ifndef PLUGIN_NONP_EVENT_H
#define PLUGIN_NONP_EVENT_H

#include <event/event.h>
#include <identifier/identifier.h>
#include <object/ptr.h>

namespace plugin {

    class common_event : public event {
    public:
        common_event(const string& name, ptr<identifier> dst, ptr<data> param = nullptr);
        common_event(const string& name, const string& dst, ptr<data> param = nullptr);
        common_event(const string& name, ptr<data> param = nullptr);
        virtual ~common_event();

    public:
        virtual ptr<plugin> deliver() const override ;
        virtual ptr<identifier> destination() const override ;
        virtual const string &event_type() const ;
        virtual ptr<data> param() const override ;

        virtual string type() const override ;
        virtual bool is_kind_of(const string &type_name) const override ;

    private:
        string m_event_name;
        ptr<plugin> m_deliver;
        ptr<identifier> m_dst;
        ptr<data> m_param;
    };

}

#endif //PLUGIN_NONP_EVENT_H
