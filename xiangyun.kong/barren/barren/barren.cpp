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

#include <lib/identifier/id_name.h>
#include <lib/lock/auto_lock.h>

#include <barren/util/barren_io.hpp>

#include <ipc.hpp>
#include <functions.h>
#include <names.h>

using namespace kxy;
using namespace pf;
using namespace std;

namespace mind {

    barren::barren() {
        m_ids = new long[2];
        m_ids[0] = 2;
        m_ids[1] = get_guid();
        
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
    
    long barren::operator[] (long i) {
        if (i + 2 <= size()) {
            return m_ids[i + 2];
        } else {
            return 0;
        }
    }
    
    long barren::size() const {
        return m_ids[0] - 2;
    }
    
    long barren::id() const {
        return m_ids[1];
    }
    
    long barren::get_guid() {
        long guid = 0;
        ptr<serializable> rsp;
        rsp = call_plugin(new id_name(PLUGIN_ID_SERVICE), F_FETCH_ADD_GUID);
        if (rsp != nullptr) {
            rsp >> guid;
        }
        return guid;
    }
    
    
    set<long> g_locked_barren;
    pthread_mutex_t g_barren_set_sync;
    pthread_cond_t g_cond_barren_unlocked;
    
    void __attribute__((constructor)) __init_barren_sync_mutex() {
        pthread_mutex_init(&g_barren_set_sync, nullptr);
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
                locked = false;
                pthread_cond_wait(&g_cond_barren_unlocked, &g_barren_set_sync);
            }
        } while(!locked);
    }
    
    void barren::unlock() {
        do {
            auto_lock _(&g_barren_set_sync);
            g_locked_barren.erase(id());
        } while (0);
        
        pthread_cond_signal(&g_cond_barren_unlocked);
    }
    
}
