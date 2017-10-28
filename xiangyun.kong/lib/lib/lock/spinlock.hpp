//
//  spinlock.hpp
//  lib
//
//  Created by 孔祥云 on 10/26/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef spinlock_h
#define spinlock_h

#include <atomic>

using namespace std;

namespace kxy {
    
    class spin_mutex {
    public:
        void lock() {
            while(flag.test_and_set(memory_order_acquire))
                ;
        }
        void unlock() {
            flag.clear(memory_order_release);
        }
    private:
        atomic_flag flag = ATOMIC_FLAG_INIT;
    };

}

#endif /* spinlock_h */
