//
// Created by 孔祥云 on 7/30/16.
//

#ifndef PLUGIN_PLUGIN_H
#define PLUGIN_PLUGIN_H

#include <lib/object/object.h>
#include <lib/identifier/identifier.h>
#include <lib/fs/xml.h>

#include <plugin/response/response.h>
#include <plugin/event/event.h>
#include <plugin/trigger/trigger.h>
#include <plugin/executor/executor.h>
#include <list>

#include <map>

using namespace std;
using namespace kxy;
using namespace rapidxml;

namespace pf {

    class plugin : public object {
    public:
        DECLARE_TYPE(object, OBJ_PLUGIN);
        
    public:
        /**
         * implementation for processing event
         * @param evt the event to process
         */
        virtual void on_event(ptr<event> evt);
        /**
         * execute pre-defined function
         * @param evt function and parameter for function
         * @return result of executing
         */
        virtual ptr<response> do_task(ptr<event> evt);

    public:
        /**
         * which functions the plugin supports.
         * other tasks won't route to here
         */
        virtual list<ptr<identifier>> supported_event() const;
        /**
         * which plugins and/or events the plugin depend on.
         * if depended object doesn't exist, the plugin would not be loaded,
         * only if it declared to
         */
        virtual list<ptr<identifier>> depend_on() const;

        virtual void init();
        virtual void uninit();

    public:
        static ptr<plugin> current_plugin();
        static ptr<object> current_task();
        
    protected:
        map<string, ptr<trigger>> m_triggers;
        map<string, ptr<executor>> m_executors;
    };

    typedef plugin* (*plugin_init_func)(xml_node<>* conf);

}

#endif //PLUGIN_PLUGIN_H
