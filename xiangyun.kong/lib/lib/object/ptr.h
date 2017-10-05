//
//  ptr.h
//  plugin-framework
//
//  Created by 孔祥云 on 10/5/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef ptr_h
#define ptr_h

namespace kxy {
    
    /**
     * @since: 9:24 PM Oct 5, 2016
     *
     * @warning ty must be derived from ::plugin::object
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
            if(_val != nullptr)
                _val->ref();
            if(m_ref != nullptr)
                m_ref->reduce();
            m_ref = _val;
            return *this;
        }
        
        ~ptr() {
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
