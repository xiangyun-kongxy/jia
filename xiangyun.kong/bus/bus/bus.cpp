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

#include <bus/trigger/trigger_on_route.h>
#include <bus/trigger/trigger_on_response.h>

#include <events.h>
#include <names.h>

#include <mutex>

using namespace std;
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

    void bus::set_waiting(ptr<kxy::identifier> id) {
        do {
            auto_lock _(&m_mutex);
            m_waiting[id] = nullptr;
        } while (0);
    }

    ptr<object> bus::wait_object(ptr<kxy::identifier> id, timeval& timeout) {
        timespec ts;
        ts.tv_sec = timeout.tv_sec;
        ts.tv_nsec = timeout.tv_usec * 1000;

        while(true) {
            auto_lock _(&m_mutex);

            map<ptr<identifier>,ptr<object>>::iterator i;
            i = m_waiting.find(id);
            if (i->second != nullptr) {
                ptr<object> obj = i->second;
                m_waiting.erase(i);
                return obj;
            }

            timeval now;
            gettimeofday(&now, nullptr);
            if (now.tv_sec > timeout.tv_sec ||
                (now.tv_sec == timeout.tv_sec &&
                 now.tv_usec >= timeout.tv_usec)) {
                    m_waiting.erase(id);
                break;
            }

            pthread_cond_timedwait(&m_changed, &m_mutex, &ts);
        }
        return nullptr;
    }

    void bus::set_object(ptr<kxy::object> obj) {
        do {
            auto_lock _(&m_mutex);

            bool set = false;
            map<ptr<identifier>, ptr<object>>::iterator it;
            for (it = m_waiting.begin(); it != m_waiting.end(); ++it) {
                if (it->first->match(obj)) {
                    it->second = obj;
                    set = true;
                }
            }

            if (set) {
                pthread_cond_broadcast(&m_changed);
            }
        } while (0);

        list<task_callback> callbacks;
        do {
            lock_guard<mutex> _(m_trigger_mutex);

            map<ptr<identifier>, task_callback>::iterator i;
            for (i = m_user_trigger.begin(); i != m_user_trigger.end(); ) {
                if (i->first->match(obj)) {
                    callbacks.push_back(i->second);
                    m_user_trigger.erase(i++);
                } else {
                    ++i;
                }
            }

        } while (0);

        for (task_callback callback : callbacks) {
            callback(obj);
        }
    }

    void bus::set_event_trigger(ptr<kxy::identifier> evt, task_callback func) {
        auto_lock _(&m_mutex);
        m_user_trigger[evt] = func;
    }

}
