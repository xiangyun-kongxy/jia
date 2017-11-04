//
// Created by 孔祥云 on 7/30/16.
//

#ifndef PLUGIN_PLUGIN_H
#define PLUGIN_PLUGIN_H

#include <lib/object/object.hpp>
#include <lib/identifier/identifier.hpp>
#include <lib/fs/xml.hpp>
#include <lib/container/cqueue.hpp>

#include <plugin/response/response.hpp>
#include <plugin/event/event.hpp>
#include <plugin/executor/executor.hpp>
#include <plugin/plugin/plugin_status.hpp>
#include <plugin/function/function.hpp>

#include <list>
#include <map>
#include <mutex>

using namespace std;
using namespace kxy;
using namespace rapidxml;

namespace pf {

    class plugin : public object {
    public:
        DECLARE_TYPE(object, OBJ_PLUGIN);

    public:
        plugin();

    public:
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
        virtual list<ptr<function>> supported_functions() const = 0;
        
        /**
         * which plugins and/or events the plugin depend on.
         * if depended object doesn't exist, the plugin would not be loaded,
         * only if it declared to
         */
        virtual list<ptr<identifier>> depend_on() const;

    public:
        virtual void init();
        virtual void suspend();
        virtual void resume();
        virtual void uninit();

    public:
        virtual plugin_status status();
        virtual ptr<cqueue<ptr<object>>> tasks();
        virtual long thread_count();
        virtual void inc_thread();
        virtual void dec_thread();
        
    public:
        static ptr<plugin> current_plugin();
        static ptr<event> current_task();
        
    protected:
        map<string, ptr<executor>> m_executors;

        plugin_status m_status;
        ptr<cqueue<ptr<object>>> m_tasks;
        
        mutex m_mutex;
        list<pthread_t> m_threads;
    };

    typedef plugin* (*plugin_init_func)(xml_node<>* conf);

}

#endif //PLUGIN_PLUGIN_H
