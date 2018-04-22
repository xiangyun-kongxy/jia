//
//  pattern.hpp
//  learning
//
//  Created by 孔祥云 on 4/14/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef pattern_hpp
#define pattern_hpp

#include "data.hpp"
#include "operater.hpp"

#include <vector>

using namespace std;
using namespace kxy;

namespace mind {
    
    class pattern : public data {
    public:
        pattern();
        pattern(ptr<barren> load_from);
        
        virtual ~pattern();
        
    public:
        void set_opt(ptr<operater> opt);
        void set_opd(const vector<ptr<data>>& opd);
        
    public:
        virtual ptr<barren> operator [] (int pos);
        virtual long size();
        virtual long version();
        
    protected:
        void try_update_data();
        
    protected:
        ptr<operater> m_opt;
        vector<ptr<data>> m_opds;
        
        ptr<data> m_rdata;
        long m_version;
    };
    
    
}

#endif /* pattern_hpp */
