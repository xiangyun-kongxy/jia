/*
 *  ps.cpp
 *  ps
 *
 *  Created by xiangyun.kong on 10/28/17.
 *  Copyright © 2017 xiangyun.kong. All rights reserved.
 *
 */

#include <iostream>

#include "ps.hpp"

#include <messages.hpp>
#include <errors.hpp>

#include <plugin/response/simple_response.hpp>

#include <ps/executor/exe_publish.hpp>

namespace pf {

    ps::ps() {
        m_publisher = new publisher;
    }

    ptr<response> ps::do_task(ptr<event> evt) {
        if (evt != nullptr) {
            m_publisher->run(this, evt);
        }
        return nullptr;
    }

    long ps::subscribe(ptr<object> what) {
        ps_index* ind = m_indexes.select(what);
        long pos = m_slot.acquire();
        ind->registe(what, pos);

        return pos;
    }

    ptr<object> ps::wait(long pos) {
        return m_slot.wait(pos);
    }

    void ps::subscribe(ptr<object> what, fcallback callback) {
        ps_index* ind = m_indexes.select(what);
        ind->registe(what, callback);
    }

    void ps::publish(ptr<object> obj) {
        for (ps_index* ind : (list<ps_index*>)m_indexes) {
            for (long pos : ind->search(obj)) {
                m_slot.release(pos, obj);
            }
        }
    }

}
