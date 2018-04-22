//
//  pattern.cpp
//  learning
//
//  Created by 孔祥云 on 4/14/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "pattern.hpp"

namespace mind {
    
    pattern::pattern() {
        m_version = 0;
    }
    
    pattern::~pattern() {
        
    }
    
    void pattern::set_opt(ptr<mind::operater> opt) {
        m_opt = opt;
    }
    
    void pattern::set_opd(const vector<ptr<mind::data> > &opd) {
        m_opds = opd;
    }
    
    long pattern::size() {
        try_update_data();
        return m_rdata->size();
    }
    
    long pattern::version() {
        try_update_data();
        return m_version;
    }
    
    ptr<barren> pattern::operator[](int pos) {
        try_update_data();
        return (**m_rdata)[pos];
    }
    
    void pattern::try_update_data() {
        long ver = 0;
        for (ptr<data> d : m_opds) {
            if (d->version() > ver)
                ver = d->version();
        }
        if (ver > version()) {
            m_rdata = m_opt->compute(m_opds);
            m_version = ver;
        }
    }
}
