//
// Created by 孔祥云 on 8/10/16.
//

#include "bus.h"
#include "bus_functions.h"
#include <constants.h>
#include <lock/auto_lock.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <executor/executor.h>
#include <identifier/id_name.h>
#include "trigger/trigger_on_routing_event.h"
#include "trigger/trigger_on_response.h"

using namespace kxy;

namespace pf {
    
    bus::bus() {
        
        m_sem = sem_open("plugin.bus.pending.task.sem", O_CREAT, 0644, 0);
        pthread_mutex_init(&m_mutex, nullptr);
        
        m_event_processor[F_ROUTE_EVENT]    = new trigger_on_routing_event;
        m_event_processor[F_RESPONSE]       = new trigger_on_response;
        
    }
    
    bus::~bus() {
        pthread_mutex_destroy(&m_mutex);
        sem_close(m_sem);
    }
    
    ptr<response> bus::wait_respond(ptr<task> tsk) {
        while(true) {
            if (0 == sem_wait(m_sem) ) {
                pthread_mutex_lock(&m_mutex);
                
                map<ptr<task>,ptr<response>>::iterator i;
                i = m_done_task.find(tsk);
                if(i != m_done_task.end()) {
                    ptr<response> r = i->second;
                    
                    m_pending_task.erase(tsk);
                    m_done_task.erase(i);
                    pthread_mutex_unlock(&m_mutex);
                    return r;
                } else {
                    pthread_mutex_unlock(&m_mutex);
                    
                    // it's not my semaphore, return back to owner
                    sem_post(m_sem);
                    usleep(16);
                }
            }
        }
        return nullptr;
    }
    
    void bus::add_pending_task(ptr<task> tsk, callback func) {
        auto_lock lock(&m_mutex);
        m_pending_task[tsk] = func;
    }
    
    void bus::add_response(ptr<task> tsk, ptr<response> rsp) {
        auto_lock lock(&m_mutex);
        
        map<ptr<task>,callback>::iterator i;
        i = m_pending_task.find(tsk);
        if(i != m_pending_task.end()) {
            if(i->second != nullptr) {
                /**
                 * @warning security problem: to use B's thread to do response
                 *          for A, A may write bad code
                 */
                i->second(tsk, rsp);
                m_pending_task.erase(i);
            } else {
                m_done_task[tsk] = rsp;
                sem_post(m_sem);
            }
        }
    }
    
    string bus::type() const {
        return "bus";
    }
    
    bool bus::is_kind_of(const string &type_name) const {
        return type_name == "bus" || plugin::is_kind_of(type_name);
    }

    ptr<serializable> pack_data() {
        return new serializable;
    }
}
