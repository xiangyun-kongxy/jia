//
//  barren.hpp
//  barren
//
//  Created by 孔祥云 on 1/1/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef barren_hpp
#define barren_hpp

#include <lib/object/reference.hpp>
#include <lib/object/ptr.hpp>
#include <lib/serialize/serializable.hpp>
#include <lib/lock/spinlock.hpp>

#include <barren/bnum.hpp>

using namespace kxy;
using namespace std;

namespace mind {
    
    /**
     * barren is the base of all stored objects in mind
     */
    class barren : public reference {
    public:
        static ptr<barren> load(long id);
        static ptr<barren> load(const string& name);
        static void save(ptr<barren> obj);
        static void save(const string& name, ptr<barren> obj);
        
    protected:
        static long get_guid();
        static long get_creator();
        
    public:
        barren(bool init = true);
        barren(const vector<long>& ids);
        barren(const initializer_list<long>& ids);
        barren(long id, const initializer_list<long>& others);
        virtual ~barren(){}
        
    public:
        long id();
        long size();
        long operator[] (long i);
        
        void add_ref();
        void del_ref();
        long get_ref();
        
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
        
    protected:
        /**
         * @param num if num is a barren then add reference
         */
        void try_add_ref(long num);
        
    protected:
        long* m_ids;
        spin_mutex m_lock;
    };
    
}

#endif /* barren_hpp */
