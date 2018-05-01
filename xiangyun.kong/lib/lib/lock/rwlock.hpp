//
//  rwlock.hpp
//  lib
//
//  Created by 孔祥云 on 4/22/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef rwlock_h
#define rwlock_h

#include <lib/lock/spinlock.hpp>
#include <pthread.h>

namespace kxy {
    
    class rwlock {
    public:
        rwlock() {
            m_nread = 0;
            pthread_mutex_init(&m_write, nullptr);
        }
        
    public:
        void read_lock() {
            m_read.lock();
            
            if (++m_nread == 1)
                pthread_mutex_lock(&m_write);
            
            m_read.unlock();
        }
        
        void read_unlock() {
            m_read.lock();
            
            if (--m_nread == 0)
                pthread_mutex_unlock(&m_write);
            
            m_read.unlock();
        }
        
        void write_lock() {
            pthread_mutex_lock(&m_write);
        }
        
        void write_unlock() {
            pthread_mutex_unlock(&m_write);
        }
        
    private:
        spin_mutex m_read;
        long m_nread;
        pthread_mutex_t m_write;
    };
    
}

#endif /* rwlock_h */
