//
//  ptr.h
//  plugin-framework
//
//  Created by 孔祥云 on 10/5/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef ptr_h
#define ptr_h

#ifdef DEBUG_REFERENCE
#   include <pthread.h>
#endif

namespace kxy {
    
    /**
     * @since: 9:24 PM Oct 5, 2016
     *
     * @warning ty must be derived from ::kxy::reference
     *
     */
    template<typename ty>
    class ptr {
    public:
        typedef ty value_type;
        
    public:
        ptr() {
            m_ref = nullptr;
        }
        
        
        ptr(ty* _p) : ptr() {
            *this = _p;
        }
        
        ptr(const ptr& _r) : ptr() {
            *this = _r;
        }
        
        const ptr& operator=(const ptr& _r) {
            return *this = _r.m_ref;
        }
        
        const ptr& operator=(ty* _val) {
#ifdef DEBUG_REFERENCE
            if (_val != nullptr) {
                printf("%016lx: %016lx +++ %016lx(%ld)\n", (long)pthread_self(),
                       (long)this, (long)_val, _val->ref_count());
            }
            if (m_ref != nullptr) {
                printf("%016lx: .\t%016lx --- %016lx(%ld)\n", (long)pthread_self(),
                       (long)this, (long)m_ref, m_ref->ref_count());
            }
#endif
            if(_val != nullptr)
                _val->ref();
            if(m_ref != nullptr)
                m_ref->reduce();
            m_ref = _val;
            return *this;
        }
        
        ~ptr() {
#ifdef DEBUG_REFERENCE
            if (m_ref != nullptr) {
                printf("%016lx .\t.\t%016lx xxx %016lx(%ld)\n", (long)pthread_self(),
                       (long)this, (long)m_ref, m_ref->ref_count());
            }
#endif
            if(m_ref != nullptr)
                m_ref->reduce();
        }
        
    public:
        ty* operator*() const {
            return m_ref;
        }
        
        ty* operator->() const {
            return m_ref;
        }
        
        bool operator==(const ty* _cmp) const {
            return m_ref == _cmp;
        }
        
        bool operator!=(const ty* _cmp) const {
            return !(*this == _cmp);
        }
        
        bool operator==(const ptr<ty>& _cmp) const {
            return m_ref == _cmp.m_ref;
        }
        
        bool operator!=(const ptr<ty>& _cmp) const {
            return !(*this == _cmp);
        }
        
        bool operator<(const ptr<ty>& _cmp) const {
            return m_ref < _cmp.m_ref;
        }
        
        template<typename inherit_type>
        operator ptr<inherit_type>() const {
            return ptr<inherit_type>((inherit_type*)m_ref);
        }
        
        template<typename any_type>
        explicit operator any_type() const {
            return (any_type)*m_ref;
        }

        template<typename type>
        ptr<ty>& operator << (type data) {
            (*m_ref) << data;
            return *this;
        }

        template<typename type>
        ptr<ty>& operator >> (type& data) {
            (*m_ref) >> data;
            return *this;
        }
        
    private:
        ty* m_ref;
    };
    
}

#endif /* ptr_h */
