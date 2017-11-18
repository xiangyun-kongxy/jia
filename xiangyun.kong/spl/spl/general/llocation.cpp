//
//  location.cpp
//  spl
//
//  Created by xiangyun.kong on 26/03/2017.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "llocation.hpp"

namespace spl {
    
    llocation::llocation(ptr<lfile> file, long line, long column, ptr<llocation> ll) {
        m_file = file;
        m_line = line;
        m_column = column;
        m_extracted_from = ll;
    }
    
    string llocation::name() const {
        if (m_extracted_from != nullptr) {
            return  m_file->name() + ":" + to_string(m_line) + "," +
            to_string(m_column) + "(from " +
            m_extracted_from->name() + ")";
            
        } else {
            return  m_file->name() + ":" + to_string(m_line) + "," +
            to_string(m_column);
        }
    }
    
    string llocation::sname() const {
        return m_file->sname() + ":" + to_string(m_line);
    }
    
    ptr<llocation> llocation::extract_from() const {
        return m_extracted_from;
    }
    
    ptr<lfile> llocation::file() const {
        return m_file;
    }
    
    long llocation::line() const {
        return m_line;
    }
    
    long llocation::column() const {
        return m_column;
    }
    
}
