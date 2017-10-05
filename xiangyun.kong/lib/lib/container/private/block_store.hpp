//
//  block_store.hpp
//  lib
//
//  Created by 孔祥云 on 1/21/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef block_store_hpp
#define block_store_hpp

namespace kxy {
    
    template<typename ty>
    class block_store {
    private:
        typedef ty original_type;
        typedef block_store<ty> compound_type;
        
    private:
        block_store() {
        }
        
    public:
        block_store(int size, int level) {
            init_block_store(size, level);
        }
        
        ~block_store() {
            if(m_level == 0) {
                delete[] (original_type*)m_store;
            } else {
                delete[] (compound_type*)m_store;
            }
        }
        
        void init_block_store(int size, int level) {
            m_block_size = size;
            m_level = level;
            m_capacity = 1;
            for(int i = 0; i <= 0; ++i) {
                m_capacity *= m_block_size;
            }
            
            if(level == 0) {
                m_store = new original_type[m_block_size];
            } else {
                m_store = new block_store<ty>[size];
                for(int i = 0; i < size; ++i) {
                    ((compound_type*)m_store + i)->init_block_store(size, level-1);
                }
            }
        }
        
        const block_store<ty>& operator= (const block_store<ty>& copy) {
            if(m_level > copy.m_level) {
                *(compound_type*)m_store = copy;
            } else if( m_level == copy.m_level) {
                if(m_level == 0) {
                    for(int i = 0; i < m_block_size; ++i) {
                        ((original_type*)m_store)[i] = ((original_type*)copy.m_store)[i];
                    }
                } else {
                    for(int i = 0; i < m_block_size; ++i) {
                        ((compound_type*)m_store)[i] = ((compound_type*)copy.m_store)[i];
                    }
                }
            }
            
            return *this;
        }
        
    public:
        long capacity() const {
            return m_capacity;
        }
        
        int block_size() const {
            return m_block_size;
        }
        
        int level() const {
            return m_level;
        }
        
        void set_value(long pos, const original_type& value) {
            if(pos < capacity()) {
                if(m_level == 0) {
                    ((original_type*)m_store)[pos] = value;
                } else {
                    long capacity_low = capacity() / block_size();
                    int block = pos / capacity_low;
                    long diff = pos % capacity_low;
                    ((compound_type*)m_store)[block].set_value(diff, value);
                }
            }
        }
        
        original_type get_value(long pos) const {
            if(pos < capacity()) {
                if(m_level == 0) {
                    return ((original_type*)m_store)[pos];
                } else {
                    long capacity_low = capacity() / block_size();
                    int block = pos / capacity_low;
                    long diff = pos % capacity_low;
                    return ((compound_type*)m_store)[block].get_value(diff);
                }
            }
            return original_type();
        }
        
    private:
        long m_capacity;
        int m_block_size;
        int m_level;
        void* m_store;
    };
    
}


#endif /* block_store_hpp */
