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

#include <messages.hpp>

namespace pf {
    
    plugin_controller::plugin_controller() {
        m_executors[M_INC_THREAD] = new class inc_thread;
        m_executors[M_DEC_THREAD] = new class dec_thread;
    }
}
