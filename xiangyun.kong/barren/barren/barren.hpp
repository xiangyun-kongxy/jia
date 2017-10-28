//
//  barren.hpp
//  barren
//
//  Created by 孔祥云 on 1/1/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef barren_hpp
#define barren_hpp

#include <atomic>
#include <string>
#include <list>

#include <lib/object/reference.hpp>
#include <lib/object/ptr.hpp>
#include <lib/serialize/serializable.hpp>

using namespace kxy;
using namespace std;

namespace mind {
    
    class barren : public reference {
    public:
        barren(bool init = true);
        barren(const list<long>& ids);
        
    public:
        virtual ~barren(){}
        
    public:
        long id() const;
        long size() const;
        long operator[] (long i);
        
    public:
        void lock();
        void unlock();
        
    public:
        
        DECL_SERIALIZE(barren, ar, ins, {
            ar << ins.m_ids[0];
            for (long i = 1; i < ins.m_ids[0]; ++i) {
                ar << ins.m_ids[i];
            }
        });
        DECL_DESERIALIZE(barren, ar, ins, {
            delete[] ins.m_ids;
            
            long size;
            ar >> size;
            ins.m_ids = new long[size];
            ins.m_ids[0] = size;
            for (long i = 1; i < size; ++i) {
                ar >> ins.m_ids[i];
            }
        });
        
    private:
        long get_guid();
        
    protected:
        long* m_ids;
    };
    
}

#endif /* barren_hpp */
