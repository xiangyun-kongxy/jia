//
// Created by 孔祥云 on 8/10/16.
//

#include "bus.h"

#include <unistd.h>
#include <sys/fcntl.h>

#include <lib/lock/auto_lock.h>
#include <lib/identifier/id_name.h>
#include <plugin/executor/executor.h>

#include <bus/trigger/trigger_on_route.h>
#include <bus/trigger/trigger_on_response.h>

#include <events.h>
#include <names.h>

using namespace kxy;

namespace pf {
    
    bus::bus() {

        pthread_cond_init(&m_changed, nullptr);
        pthread_mutex_init(&m_mutex, nullptr);
        
        m_event_processor[EVT_ROUTE]        = new on_route;
        m_event_processor[EVT_RESPONSE]     = new on_response;
        
    }
    
    bus::~bus() {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_changed);
    }

    void bus::hold_object(ptr<identifier> id) {
        auto_lock _(&m_mutex);
        m_hold_object.insert(id);
    }
    
    void bus::release_object(ptr<identifier> id) {
        auto_lock _(&m_mutex);
        m_hold_object.erase(id);

        list<ptr<object>>::iterator i;
        for (i = m_object_set.begin(); i != m_object_set.end(); ) {
            if (id->match(*i)) {
                m_object_set.erase(i++);
            } else {
                ++i;
            }
        }
    }
    
    ptr<object> bus::wait_object(ptr<kxy::identifier> id) {
        pthread_mutex_lock(&m_mutex);
        m_waiting_object.push_back(id);
        pthread_mutex_unlock(&m_mutex);

        while(true) {
            auto_lock _(&m_mutex);

            for (ptr<object> obj : m_object_set) {
                if (id->match(obj)) {
                    list<ptr<identifier>>::iterator i;
                    for (i = m_waiting_object.begin();
                         i != m_waiting_object.end(); ++i) {
                        if (*i == id) {
                            m_waiting_object.erase(i);
                            break;
                        }
                    }
                    return obj;
                }
            }
            
            pthread_cond_wait(&m_changed, &m_mutex);
        }
        return nullptr;
    }

    void bus::set_object(ptr<kxy::object> obj) {
        auto_lock _(&m_mutex);

        bool held = false;

        for (ptr<identifier> id : m_waiting_object) {
            if (id->match(obj)) {
                m_object_set.push_back(obj);
                held = true;
                pthread_cond_signal(&m_changed);
                break;
            }
        }
        if (!held) {
            for (ptr<identifier> id : m_hold_object) {
                if (id->match(obj)) {
                    m_object_set.push_back(obj);
                    break;
                }
            }
        }
        
        map<ptr<identifier>, task_callback>::iterator i;
        for (i = m_user_trigger.begin(); i != m_user_trigger.end(); ) {
            if (i->first->match(obj)) {
                i->second(obj);
                m_user_trigger.erase(i++);
            } else {
                ++i;
            }
        }
    }

    void bus::set_event_trigger(ptr<kxy::identifier> evt, task_callback func) {
        auto_lock _(&m_mutex);
        m_user_trigger[evt] = func;
    }

}
