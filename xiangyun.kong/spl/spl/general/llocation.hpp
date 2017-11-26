//
//  location.hpp
//  spl
//
//  Created by xiangyun.kong on 26/03/2017.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef location_hpp
#define location_hpp

#include <spl/general/lfile.hpp>

namespace spl {
    
    class llocation : public reference {
    public:
        llocation(ptr<lfile> file, long line, long column, ptr<llocation> ll);
        
        llocation* dup() {
            llocation* pn;
            pn = new llocation(m_file, m_line, m_column, m_extracted_from);
            pn->pos() = m_pos;
            return pn;
        }
        
    public:
        string name() const;
        string sname() const;
        
    public:
        ptr<llocation> extract_from() const;
        ptr<lfile> file() const;
        long& line();
        long& column();
        long& pos();
        
    private:
        ptr<llocation> m_extracted_from;
        
        ptr<lfile> m_file;
        long m_line;
        long m_column;
        long m_pos;
    };
    
}

#endif /* location_hpp */
