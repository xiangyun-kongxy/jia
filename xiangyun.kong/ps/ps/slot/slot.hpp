//
//  slot.hpp
//  ps
//
//  Created by xiangyun.kong on 10/28/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef slot_hpp
#define slot_hpp

#include <stdio.h>

#include <lib/object/object.hpp>
#include <lib/object/ptr.hpp>
#include <lib/container/cqueue.hpp>

#include <sys/semaphore.h>
#include <iostream>

using namespace kxy;
using namespace std;

#define MAX_SLOT_NUM    1024

namespace pf {

    class slot {
    public:
        slot() {
            m_pfree = new cqueue<long>;

            for (long i = 0; i < MAX_SLOT_NUM; ++i) {
                m_sems[i] = sem_open((to_string(i) + "__ps_slot").c_str(),
                                     O_CREAT, 0644, 0);
                m_pfree->push(i);
            }
        }

        ~slot() {
            for (long i = 0; i < MAX_SLOT_NUM; ++i) {
                sem_close(m_sems[i]);
            }
        }
        
    public:
        long acquire() {
            long pos = m_pfree->pop();
            return pos;
        }

        void release(long pos, ptr<object> obj) {
            m_objects[pos] = obj;
            sem_post(m_sems[pos]);
            m_pfree->push(pos);
        }

        ptr<object> wait(long pos) {
            sem_wait(m_sems[pos]);
            return m_objects[pos];
        }

    private:
        ptr<cqueue<long>> m_pfree;
        sem_t* m_sems[MAX_SLOT_NUM];

        ptr<object> m_objects[MAX_SLOT_NUM];
    };
    
}

#endif /* slot_hpp */
