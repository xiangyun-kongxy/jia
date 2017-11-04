/*
 *  plugin_controller.cpp
 *  plugin_controller
 *
 *  Created by 孔祥云 on 10/29/17.
 *  Copyright © 2017 孔祥云. All rights reserved.
 *
 */

#include "plugin_controller.hpp"

#include <plugin_controller/executor/exe_inc_thread.hpp>
#include <plugin_controller/executor/exe_dec_thread.hpp>
#include <plugin_controller/executor/exe_show_task_count.hpp>
#include <plugin_controller/executor/exe_show_plugins.hpp>
#include <plugin_controller/executor/exe_show_thread_count.hpp>

namespace pf {
    
    plugin_controller::plugin_controller() {
        m_executors[M_INC_THREAD] = new class inc_thread;
        m_executors[M_DEC_THREAD] = new class dec_thread;
        m_executors[M_SHOW_TASK_COUNT] = new  show_task_count;
        m_executors[M_SHOW_PLUGINS] = new show_plugins;
        m_executors[M_SHOW_THREAD_COUNT] = new show_thread_count;
    }
    
    extern "C" plugin* init_plugin_controller(xml_node<>* conf) {
        return new plugin_controller;
    }
}
