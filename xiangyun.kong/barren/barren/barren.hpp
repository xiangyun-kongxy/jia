//
//  barren.hpp
//  barren
//
//  Created by 孔祥云 on 1/1/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef barren_hpp
#define barren_hpp

#include <object/reference.h>
#include <object/ptr.h>
#include <atomic>
#include <string>
#include <list>

#include <serialize/serializable.hpp>

using namespace kxy;
using namespace std;

namespace mind {
    
    class barren : public reference {
    public:
        barren();
        barren(const list<long>& ids);
        
    public:
        virtual ~barren(){}
        
    public:
        long id() const;
        long operator[] (long i);
        
    public:
        static void set_gid(long id);
        static long get_gid();
        static long get_add_gid();
        
        DECL_SERIALIZE(barren, ar, ins, {
            ar << ins.m_ids[0];
            for (long i = 0; i <= ins.m_ids[0]; ++i) {
                ar << ins.m_ids[0];
            }
        })
        DECL_DESERIALIZE(barren, ar, ins, {
            long size;
            ar >> size;
            ins.m_ids = new long[size + 1];
            ins.m_ids[0] = size;
            for (long i = 1; i <= size; ++i) {
                ar >> ins.m_ids[i];
            }
        })
        
    private:
        long* m_ids;
        
        static atomic_long s_cur_id;
    };
    
}

#endif /* barren_hpp */
