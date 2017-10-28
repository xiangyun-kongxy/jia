//
//  auto_lock.h
//  plugin-framework
//
//  Created by 孔祥云 on 10/5/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef auto_lock_h
#define auto_lock_h

#include <pthread.h>

namespace kxy {
    
    class auto_lock {
    public:
        auto_lock(pthread_mutex_t* mutex) {
            m_mutex = mutex;
            pthread_mutex_lock(m_mutex);
        }
        
        ~auto_lock() {
            pthread_mutex_unlock(m_mutex);
        }
        
    private:
        pthread_mutex_t* m_mutex;
    };
    
}

#endif /* auto_lock_h */
