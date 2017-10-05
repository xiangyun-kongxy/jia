//
//  barren.cpp
//  barren
//
//  Created by 孔祥云 on 1/1/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "barren.hpp"
#include "util/barren_io.hpp"
#include <convert/basic_type_convert.h>

using namespace kxy;

namespace mind {
    atomic_long barren::s_cur_id;

    barren::barren() {
        m_ids = nullptr;
    }
    
    barren::barren(const list<long>& ids) {
        m_ids = new long[ids.size()+2];
        m_ids[0] = ids.size() + 1;
        m_ids[1] = get_add_gid();
        
        long i = 2;
        list<long>::const_iterator it = ids.begin();
        while (it != ids.end()) {
            m_ids[i] = *it;
            ++it;
            ++i;
        }
    }
    
    long barren::operator[] (long i) {
        if (i <= m_ids[0]) {
            return m_ids[i];
        } else {
            return 0;
        }
    }
    
    long barren::id() const {
        return m_ids[1];
    }
    
    void barren::set_gid(long id) {
        atomic_store(&s_cur_id, id);
    }
    
    long barren::get_gid() {
        return atomic_load(&s_cur_id);
    }
    
    long barren::get_add_gid() {
        return atomic_fetch_add(&s_cur_id, 1L);
    }

}
