//
//  reference.h
//  lib
//
//  Created by 孔祥云 on 11/4/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef reference_h
#define reference_h

#include <atomic>
#include <stdio.h>

using namespace std;

namespace kxy {
    
class reference {
    public:
        void ref() {
            atomic_fetch_add(&m_ref, 1L);
        }
        
        void reduce() {
            if(atomic_fetch_sub(&m_ref, 1L) == 1L) {
                delete this;
            }
        }
        
        long ref_count() const {
            return atomic_load(&m_ref);
        }
        
    public:
        reference() :
        m_ref(0L) {
#ifdef _DEBUG
                printf("%016lx is creating\n", (long)this);
#endif
        }
        
        reference(long cur_ref) :
        m_ref(cur_ref) {
#ifdef _DEBUG
                printf("%016lx is creating\n", (long)this);
#endif
        }
        
        virtual ~reference() {
#ifdef _DEBUG
                printf(".\t.\t.\t%016lx is deleting\n", (long)this);
#endif
        }
        
    private:
        atomic_long m_ref;
    };
    
}

#endif /* reference_h */
