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
#include <plugin/task/task.h>
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
         * @param tsk function and parameter for function
         * @return result of executing
         */
        virtual ptr<response> do_task(ptr<task> tsk);

    public:
        /**
         * which events the plugin supports.
         * other events won't route to here
         */
        virtual list<ptr<identifier>> accepted_event() const;
        /**
         * which tasks(functions) the plugin supports.
         * other tasks won't route to here
         */
        virtual list<ptr<identifier>> accepted_task() const;
        /**
         * which plugins and/or tasks, events the plugin depend on.
         * if depended object doesn't exist, the plugin would not be loaded,
         * only if it declared to
         */
        virtual list<ptr<identifier>> depend_on() const;

    public:
        static ptr<plugin> current_plugin();
        
    protected:
        map<string, ptr<trigger>> m_event_processor;
        map<string, ptr<executor>> m_task_processor;
    };

    typedef plugin* (*plugin_init_func)(xml_node<>* conf);

}

#endif //PLUGIN_PLUGIN_H
