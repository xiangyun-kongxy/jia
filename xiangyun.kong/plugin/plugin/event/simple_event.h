//
// Created by 孔祥云 on 8/2/16.
//

#ifndef PLUGIN_SIMPLE_EVENT_H
#define PLUGIN_SIMPLE_EVENT_H

#include <plugin/event/event.h>
#include <lib/identifier/identifier.h>
#include <lib/object/ptr.h>

namespace pf {

    class simple_event : public event {
    public:
        DECLARE_TYPE(event, OBJ_SIMPLE_EVENT);

    public:
        simple_event(const string& name);
        simple_event(const string& name, ptr<serializable> param);
        simple_event(const string& name, ptr<identifier> dst);
        simple_event(const string& name, ptr<serializable> param,
                     ptr<identifier> dst);

    public:
        virtual ptr<plugin> deliver() const override ;
        virtual ptr<identifier> destination() const override ;
        virtual const string &event_type() const ;
        virtual ptr<serializable> param() const override ;

    public:
        string name() const override {
            return m_event_name;
        }
        
    private:
        string m_event_name;
        ptr<plugin> m_deliver;
        ptr<identifier> m_dst;
        ptr<serializable> m_param;
    };

}

#endif //PLUGIN_SIMPLE_EVENT_H
