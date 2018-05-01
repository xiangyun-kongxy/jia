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
#include <common/config/config_service.hpp>

#include <ipc.hpp>
#include <messages.hpp>

using namespace kxy;
using namespace pf;
using namespace std;

namespace mind {

    barren::barren(bool init /*= true*/ ) {
        if (init) {
            m_ids = new long[4];
            m_ids[0] = 4;
            m_ids[1] = get_guid();
            m_ids[2] = get_creator();
            m_ids[3] = 1;
        } else {
            m_ids = nullptr;
        }
    }
    
    barren::barren(const vector<long>& ids) {
        m_ids = new long[ids.size() + 4];
        m_ids[0] = ids.size() + 4;
        m_ids[1] = get_guid();
        m_ids[2] = get_creator();
        m_ids[3] = 1;
        
        long i = 4;
        for (long it : ids) {
            m_ids[i] = it;
            try_add_ref(it);
            ++i;
        }
    }
    
    barren::barren(const initializer_list<long>& ids) {
        m_ids = new long[ids.size() + 4];
        m_ids[0] = ids.size() + 4;
        m_ids[1] = get_guid();
        m_ids[2] = get_creator();
        m_ids[3] = 1;
        
        long i = 4;
        for (long it : ids) {
            m_ids[i] = it;
            try_add_ref(it);
            ++i;
        }
    }
    
    barren::barren(long id, const initializer_list<long>& others) {
        m_ids = new long[others.size() + 4];
        m_ids[0] = others.size() + 4;
        m_ids[1] = id;
        m_ids[2] = get_creator();
        m_ids[3] = 1;
        
        long i = 4;
        for (long it : others) {
            m_ids[i] = it;
            try_add_ref(it);
            ++i;
        }
    }
    
    long barren::operator[] (long i) {
        m_lock.lock();
        
        long r;
        if (i >= size()) {
            long* ids = new long[i+3];
            ids[0] = i + 3;
            ids[i+2] = 0;
            for (long n = 1; n < i + 2; ++n) {
                ids[n] = m_ids[n];
            }
            delete[] m_ids;
            m_ids = ids;
        }
        r = m_ids[i + 2];
        
        m_lock.unlock();
        
        return r;
    }
    
    long barren::size() {
        m_lock.lock();
        long r = m_ids[0] - 2;
        m_lock.unlock();
        
        return r;
    }
    
    long barren::id() {
        m_lock.lock();
        long r = m_ids[1];
        m_lock.unlock();
        
        return r;
    }
    
    void barren::add_ref() {
        m_lock.lock();
        ++m_ids[3];
        m_lock.unlock();
    }
    
    void barren::del_ref() {
        m_lock.lock();
        --m_ids[3];
        m_lock.unlock();
    }
    
    long barren::get_ref() {
        long ref;
        
        m_lock.lock();
        ref = m_ids[3];
        m_lock.unlock();
        
        return ref;
    }
    
    void barren::try_add_ref(long num) {
        bnum::num_type type;
        long id = bnum::decode(num, &type);
        if (type == bnum::num_type::NT_BARREN) {
            ptr<barren> b = load(id);
            if (b != nullptr)
                b->add_ref();
        }
    }
    
    ptr<identifier> g_cache_provider = new id_name(PLUGIN_BARREN_CACHE);
    
    ptr<barren> barren::load(long id) {
        ptr<barren> barren;
        ptr<serializable> rsp;
        rsp = call_plugin(g_cache_provider, M_LOAD_CACHE_BARREN, id);
        if (rsp != nullptr) {
            rsp >> barren;
        }
        return barren;
    }
    
    void barren::save(ptr<barren> obj) {
        send_to(g_cache_provider, M_SAVE_CACHE_BARREN, obj);
    }
    
    ptr<barren> barren::load(const string& name) {
        long id = read_config<long>(name);
        return load(id);
    }
    
    void barren::save(const string& name, ptr<barren> obj) {
        save_config(name, obj->id());
        save(obj);
    }
    
    long barren::get_guid() {
        static long cur = 0;
        static long max = 0;
        static spin_mutex lock;

        long r = 0;
        
        lock.lock();
        if (cur >= max) {
            ptr<serializable> rsp;
            rsp = call_plugin(new id_name(PLUGIN_ID_SERVICE),
                              M_FETCH_ADD_GUID_BENCH, 10000L);
            if (rsp != nullptr) {
                rsp >> cur;
                max = cur + 10000L;
            }
        }
        if (cur < max)
            r = cur++;
        lock.unlock();
        
        return r;
    }
    
    long barren::get_creator() {
        static map<string, long> creators;
        
        long id;
        string name;
        
        ptr<plugin> pl = plugin::current_plugin();
        if (pl != nullptr)
            name = pl->name();
        else
            name = "unknown";
        
        id = creators[name];
        if (id == 0) {
            id = read_config<long>(name);
            creators[name] = id;
        }
        
        return id;
    }

}
