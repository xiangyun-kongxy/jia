//
//  cqueue.h
//  lib
//
//  Created by 孔祥云 on 11/10/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef cqueue_h
#define cqueue_h

#include <sys/fcntl.h>
#include <semaphore.h>
#include <lock/auto_lock.h>
#include <object/reference.h>
#include <pthread.h>
#include <queue>
#include <string>

using namespace std;

namespace kxy {
    
    template<typename ty>
    class cqueue : public reference {
    public:
        cqueue() {
            m_sem = sem_open(to_string((long)this).c_str(), O_CREAT, 0644, 0);
            pthread_mutex_init(&m_mutex, nullptr);
        }
        
        virtual ~cqueue() {
            pthread_mutex_destroy(&m_mutex);
        }
        
    public:
        void push(ty value) {
            auto_lock lock(&m_mutex);
            if (0 == sem_post(m_sem)) {
                m_container.push(value);
            }
        }
        
        ty pop() {
            if (sem_wait(m_sem) == 0) {
                auto_lock lock(&m_mutex);
                if (m_container.size() > 0) {
                    ty result = m_container.front();
                    m_container.pop();
                    return result;
                } else {
                    return ty();
                }
            } else {
                return ty();
            }
        }
        
        ty front() const {
            auto_lock lock(&m_mutex);
            if (m_container.size() > 0) {
                return m_container.front();
            } else {
                return ty();
            }
        }

        int size() const {
            auto_lock lock(&m_mutex);
            return m_container.size();
        }
        
    private:
        queue<ty> m_container;
        pthread_mutex_t m_mutex;
        sem_t* m_sem;
    };
}

#endif /* cqueue_h */
