//
//  part_attr.cpp
//  gower
//
//  Created by 孔祥云 on 3/17/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "part_attr.hpp"

namespace mind {
    
    part_attr::part_attr() {
        m_string = "";
        m_frequence = 1;
    }
    
    part_attr::part_attr(const string& str) {
        m_string = str;
        m_frequence = 1;
    }
    
    long& part_attr::barren() {
        return m_barren;
    }
    
    long& part_attr::frequence() {
        return m_frequence;
    }
    
    string& part_attr::str() {
        return m_string;
    }
    
}
