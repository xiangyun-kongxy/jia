//
//  barren_set.cpp
//  barren
//
//  Created by 孔祥云 on 10/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "barren_set.hpp"

#include <barren/util/barren_io.hpp>

namespace mind {
    
    void barren_set::add(long id) {
        m_ids = (long*)realloc(m_ids, (m_ids[0]+1) * sizeof(long));
        m_ids[m_ids[0]] = id;
        ++m_ids[0];
        
        save_barren(this);
    }
    
    void barren_set::remove(long id) {
        if (contain(id)) {
            long* ids = new long[m_ids[0]-1];
            ids[0] = m_ids[0] - 1;
            ids[1] = m_ids[1];
            
            long found = 0;
            for (long i = 2; i < ids[0]; ++i) {
                if (m_ids[i] == id) {
                    found = 1;
                }
                ids[i] = m_ids[i + found];
            }
            
            delete [] m_ids;
            m_ids = ids;
        }
    }
    
    bool barren_set::contain(long id) {
        for (long i = 0; i < size(); ++i) {
            if ((*(barren_set*)this)[i] == id) {
                return true;
            }
        }
        
        return false;
    }
    
}
