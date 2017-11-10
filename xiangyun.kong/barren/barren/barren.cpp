//
//  barren.cpp
//  barren
//
//  Created by 孔祥云 on 1/1/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "barren.hpp"

#include <set>
#include <semaphore.h>

#include <lib/identifier/id_name.hpp>
#include <lib/lock/auto_lock.hpp>
#include <lib/init/initializer.hpp>

#include <ipc.hpp>
#include <messages.hpp>

using namespace kxy;
using namespace pf;
using namespace std;

namespace mind {

    barren::barren(bool init /*= true*/ ) {
        if (init) {
            m_ids = new long[2];
            m_ids[0] = 2;
            m_ids[1] = get_guid();
        } else {
            m_ids = nullptr;
        }
    }
    
    barren::barren(const list<long>& ids) {
        m_ids = new long[ids.size()+2];
        m_ids[0] = ids.size() + 2;
        m_ids[1] = get_guid();
        
        long i = 2;
        for (long it : ids) {
            m_ids[i] = it;
            ++i;
        }
    }
    
    barren::barren(const initializer_list<long>& ids) {
        m_ids = new long[ids.size()+2];
        m_ids[0] = ids.size() + 2;
        m_ids[1] = get_guid();
        
        long i = 2;
        for (long it : ids) {
            m_ids[i] = it;
            ++i;
        }
    }
    
    
    long barren::operator[] (long i) {
        if (i >= size()) {
            lock();
            
            long* ids = new long[i+3];
            ids[0] = i + 3;
            ids[i+2] = 0;
            for (long n = 1; n < i + 2; ++n) {
                ids[n] = m_ids[n];
            }
            delete[] m_ids;
            m_ids = ids;
            
            unlock();
        }
        return m_ids[i + 2];
    }
    
    long barren::size() const {
        return m_ids[0] - 2;
    }
    
    long barren::id() const {
        return m_ids[1];
    }
    

    
    set<long> g_locked_barren;
    pthread_mutex_t g_barren_set_sync;
    pthread_cond_t g_cond_barren_unlocked;
    
    void __uninit_barren_sync_mutex() {
        pthread_cond_destroy(&g_cond_barren_unlocked);
        pthread_mutex_destroy(&g_barren_set_sync);
    }
    
    void __attribute__((constructor)) __init_barren_sync_mutex() {
        pthread_mutex_init(&g_barren_set_sync, nullptr);
        pthread_cond_init(&g_cond_barren_unlocked, nullptr);
        
        register_uninitializer("uninitialize barren sync", __uninit_barren_sync_mutex);
    }
    
    void barren::lock() {
        bool locked = false;
        do {
            auto_lock _(&g_barren_set_sync);
            set<long>::iterator i;
            i = g_locked_barren.find(id());
            if (i == g_locked_barren.end()) {
                g_locked_barren.insert(id());
                locked = true;
            } else {
                pthread_cond_wait(&g_cond_barren_unlocked, &g_barren_set_sync);
            }
        } while(!locked);
    }
    
    void barren::unlock() {
        do {
            auto_lock _(&g_barren_set_sync);
            g_locked_barren.erase(id());
        } while (0);
        
        pthread_cond_broadcast(&g_cond_barren_unlocked);
    }

    long barren::get_guid() {
        static long cur = 0;
        static long max = 0;

        do {
            auto_lock _(&g_barren_set_sync);
            if (cur == max) {
                ptr<serializable> rsp;
                rsp = call_plugin(new id_name(PLUGIN_ID_SERVICE),
                                  M_FETCH_ADD_GUID_BENCH, 10000L);
                if (rsp != nullptr) {
                    rsp >> cur;
                    max = cur + 10000L;
                } else {
                    return 0;
                }
            }
            return cur++;
        } while (0);
    }

}
