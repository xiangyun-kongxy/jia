//
//  part_attr.hpp
//  gower
//
//  Created by 孔祥云 on 3/17/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef part_attr_hpp
#define part_attr_hpp

#include <stdio.h>

#include <lib/serialize/serializable.hpp>
#include <lib/serialize/decl_serializable.hpp>

using namespace kxy;

namespace mind {
    
    class part_attr {
    public:
        part_attr();
        part_attr(const string& str);
        
    public:
        long& frequence();
        long& barren();
        string& str();
        
    private:
        string m_string;
        long m_frequence;
        long m_barren;
        
    public:
        DECL_SERIALIZE(part_attr, ar, ins, {
            ar << ins.m_frequence;
        });
        DECL_DESERIALIZE(part_attr, ar, ins, {
            ar >> ins.m_frequence;
        });
    };
    
}

#endif /* part_attr_hpp */
