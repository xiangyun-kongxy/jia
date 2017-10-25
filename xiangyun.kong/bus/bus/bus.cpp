//
// Created by 孔祥云 on 8/10/16.
//

#include "bus.h"

#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/time.h>

#include <lib/lock/auto_lock.h>
#include <lib/identifier/id_name.h>
#include <plugin/executor/executor.h>

#include <events.h>
#include <names.h>

#include <mutex>

using namespace std;
using namespace kxy;

namespace pf {
    
    bus::bus() {
        pthread_cond_init(&m_obj_changed, nullptr);
        pthread_mutex_init(&m_obj_mutex, nullptr);
        
        pthread_cond_init(&m_rsp_changed, nullptr);
        pthread_mutex_init(&m_rsp_mutex, nullptr);
        
        m_router = new on_route;
    }
    
    bus::~bus() {
        pthread_mutex_destroy(&m_obj_mutex);
        pthread_cond_destroy(&m_obj_changed);
        
        pthread_mutex_destroy(&m_rsp_mutex);
        pthread_cond_destroy(&m_rsp_changed);
    }
    
    void bus::on_event(ptr<pf::event> evt) {
        if (evt == nullptr) {
            return;
        } else if (evt->is_kind_of(OBJ_RESPONSE)) {
            add_response((ptr<response>)evt);
        } else {
            add_object(evt);
            m_router->happen(this, evt);
        }
    }
    
    ptr<response> bus::do_task(ptr<event> evt) {
        on_event(evt);
        return nullptr;
    }
    

    void bus::add_waiting_object(ptr<kxy::identifier> id) {
        auto_lock _(&m_obj_mutex);
        m_waiting_objects[id] = nullptr;
    }

    ptr<object> bus::wait_object(ptr<kxy::identifier> id, timeval& timeout) {
        timespec ts;
        ts.tv_sec = timeout.tv_sec;
        ts.tv_nsec = timeout.tv_usec * 1000;

        while(!__is_timeout(timeout)) {
            auto_lock _(&m_obj_mutex);

            map<ptr<identifier>,ptr<object>>::iterator i;
            i = m_waiting_objects.find(id);
            if (i->second != nullptr) {
                ptr<object> obj = i->second;
                m_waiting_objects.erase(i);
                return obj;
            }

            pthread_cond_timedwait(&m_obj_changed, &m_obj_mutex, &ts);
        }
        return nullptr;
    }

    void bus::add_object(ptr<object> obj) {
        do {
            auto_lock _(&m_obj_mutex);

            bool set = false;
            map<ptr<identifier>, ptr<object>>::iterator it;
            for (it = m_waiting_objects.begin(); it != m_waiting_objects.end(); ++it) {
                if (it->first->match(obj)) {
                    it->second = obj;
                    set = true;
                }
            }

            if (set) {
                pthread_cond_broadcast(&m_obj_changed);
            }
        } while (0);
    }

    void bus::add_response(ptr<response> rsp) {
        list<fcallback> callbacks;
        do {
            auto_lock _(&m_rsp_mutex);

            map<ptr<event>, fcallback>::iterator i;
            i = m_rsp_trigger.find(rsp->org_event());
            if (i != m_rsp_trigger.end()) {
                if (i->second != nullptr) {
                    i->second(rsp);
                }
            } else {
                m_rsps[rsp->org_event()] = rsp;
                pthread_cond_broadcast(&m_rsp_changed);
            }
        } while (0);
        
        ptr<event> evt = rsp->org_event();
        info_log(logs::get_logger("bus"), evt->name() + " " +
                 evt->deliver()->name() + " <- " +
                 evt->destination()->name());
    }
    
    void bus::add_rsp_trigger(ptr<event> evt, fcallback func) {
        auto_lock _(&m_rsp_mutex);
        if (func != nullptr) {
            m_rsp_trigger[evt] = func;
        } else {
            m_rsps[evt] = nullptr;
        }
    }

    ptr<response> bus::wait_response(ptr<pf::event> evt, timeval &timeout) {
        timespec ts;
        ts.tv_sec = timeout.tv_sec;
        ts.tv_nsec = timeout.tv_usec * 1000;
        
        while(!__is_timeout(timeout)) {
            auto_lock _(&m_rsp_mutex);
            
            map<ptr<event>, ptr<response>>::iterator i;
            i = m_rsps.find(evt);
            if (i->second != nullptr) {
                ptr<response> rsp = i->second;
                m_rsps.erase(i);
                return rsp;
            }
            
            pthread_cond_timedwait(&m_rsp_changed, &m_rsp_mutex, &ts);
        }
        return nullptr;
    }
    
    bool bus::__is_timeout(const timeval &timeout) {
        timeval now;
        gettimeofday(&now, nullptr);
        if (now.tv_sec > timeout.tv_sec) {
            return true;
        } else if (now.tv_sec < timeout.tv_sec) {
            return false;
        } else if (now.tv_usec > timeout.tv_usec) {
            return true;
        } else {
            return false;
        }
    }
}
