//
//  serializable.hpp
//  lib
//
//  Created by 孔祥云 on 7/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef serializable_hpp
#define serializable_hpp

#include "../convert/basic_type_convert.h"
#include "../object/reference.h"
#include "decl_serializable.h"
#include "../object/ptr.h"

#include <stdio.h>
#include <sstream>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <assert.h>

using namespace std;

namespace kxy {

    class serializable : public reference {
    public:
        serializable();
        serializable(const char* buf);
        
    public:
        string buf() {
            if (m_buf.size() == 0) {
                return "";
            }
            
            list<string>::const_iterator i = m_buf.begin();
            string str = *i++;
            while (i != m_buf.end()) {
                str = str + SS1 + *i++;
            }
            return str;
        }
        
    public:
        
#define def_serialize_type(type_name)           \
    serializable& operator << (type_name c) {   \
        save(c);                                \
        return *this;                           \
    }                                           \
    serializable& operator >> (type_name& c) {  \
        load(c);                                \
        return *this;                           \
    }

#define def_serialize_iterator(type_name)                       \
    serializable& operator << (const type_name& c) {            \
        *this << c.size();                                      \
        typename type_name::const_iterator i = c.begin();       \
        while (i != c.end()) {                                  \
            *this << *i;                                        \
        }                                                       \
        return *this;                                           \
    }                                                           \

        
        def_serialize_type(char);
        def_serialize_type(unsigned char);
        def_serialize_type(short);
        def_serialize_type(unsigned short);
        def_serialize_type(int);
        def_serialize_type(unsigned int);
        def_serialize_type(long);
        def_serialize_type(unsigned long);
        def_serialize_type(long long);
        def_serialize_type(unsigned long long);
        def_serialize_type(float);
        def_serialize_type(double);
        def_serialize_type(long double);
        
        template<class value_type>
        def_serialize_iterator(list<value_type>);
        template<class value_type>
        def_serialize_iterator(queue<value_type>);
        template<class value_type>
        def_serialize_iterator(stack<value_type>);
        
        
        
        
        template<class key_type, class value_type>
        serializable& operator << (const map<key_type, value_type>& m) {
            *this << m.size();
            typename map<key_type, value_type>::const_iterator i = m.begin();
            while (i != m.end()) {
                *this << i->first;
                *this << i->second;
            }
            return *this;
        }
        
        template<class value_type>
        serializable& operator << (value_type v[]) {
            assert("pointer type is not allowed");
            return *this;
        }
        
        serializable& operator << (const char* str) {
            long len = strlen(str);
            long count = len / sizeof(long);
            long i = count * sizeof(long);
            long last = 0;
            for (long j = 0; j < len - i; ++j) {
                ((char*)&last)[j] = str[i+j];
            }
            
            *this << len;
            for (i = 0; i < count; ++i) {
                *this << ((const long*)str)[i];
            }
            *this << last;
            
            return *this;
        }
        
        serializable& operator >> (string& str) {
            long len = s2l(m_buf.front().c_str());
            m_buf.pop_front();
            
            char* buf = new char[(len / sizeof(long) + 1) * sizeof(long)];
            long i;
            for (i = 0; i < len / sizeof(long); ++i) {
                ((long*)buf)[i] = s2l(m_buf.front().c_str());
                m_buf.pop_front();
            }
            long last = s2l(m_buf.front().c_str());
            m_buf.pop_front();
            ((long*)buf)[i] = last;

            str = buf;
            delete[] buf;
            return *this;
        }
        serializable& operator << (const string& str) {
            return (*this) << str.c_str();
        }
        
        template<class key_type, class value_type>
        serializable& operator >> (map<key_type, value_type>& m) {
            long size;
            *this >> size;
            for (long i = 0; i < size; ++i) {
                key_type key;
                value_type value;
                *this >> key >> value;
                m[key] = value;
            }
            return *this;
        }
        
        template<class value_type>
        serializable& operator >> (list<value_type>& l) {
            long size;
            *this >> size;
            for (long i = 0; i < size; ++i) {
                value_type value;
                *this >> value;
                l.push_back(value);
            }
            return *this;
        }
        
        template<class value_type>
        serializable& operator >> (queue<value_type>& l) {
            long size;
            *this >> size;
            for (long i = 0; i < size; ++i) {
                value_type value;
                *this >> value;
                l.push(value);
            }
            return *this;
            
        }
        
        template<class value_type>
        serializable& operator >> (stack<value_type>& l) {
            long size;
            *this >> size;
            for (long i = 0; i < size; ++i) {
                value_type value;
                *this >> value;
                l.push(value);
            }
            return *this;
        }
        
        template<class value_type>
        serializable& operator >> (value_type v[]) {
            assert("pointer type is not allowed");
            return *this;
        }

        template<class type>
        serializable& operator << (ptr<type> data) {
            long p = (long)*data;
            *this << p;
            return *this;
        }

        template<class type>
        serializable& operator >> (ptr<type>& data) {
            long p;
            *this >> p;
            data = (type*)p;
            return *this;
        }
        
    private:
        template<class base_type>
        void save(base_type value) {
            long diff_size = sizeof(unsigned long) - sizeof(base_type);
            
            if (diff_size > 0) {
                long r = 0;
                *(base_type*)(((char*)&r) + diff_size) = value;
                m_buf.push_back(l2s(r));
            } else if (diff_size == 0) {
                m_buf.push_back(l2s(*(unsigned long*)&value));
            } else {
                long size = sizeof(base_type) / sizeof(unsigned long);
                m_buf.push_back(l2s(size));
                for (long i = 0; i < size; ++i) {
                    m_buf.push_back(l2s(((unsigned long*)&value)[i]));
                }
            }
        }
        
        template<class base_type>
        void load(base_type& value) {
            long diff_size = sizeof(unsigned long) - sizeof(base_type);
            
            if (diff_size > 0) {
                long r = s2l(m_buf.front().c_str());
                value = *(base_type*)(((char*)&r) + diff_size);
                m_buf.pop_front();
            } else if (diff_size == 0) {
                long r = s2l(m_buf.front().c_str());
                value = *(base_type*)&r;
                m_buf.pop_front();
            } else {
                long size = s2l(m_buf.front().c_str());
                m_buf.pop_front();
                
                for (long i = 0; i < size; ++i) {
                    long r = s2l(m_buf.front().c_str());
                    m_buf.pop_front();
                    ((long*)&value)[i] = r;
                }
            }
        }

    private:
        list<string> m_buf;
    };
    
    
}

#endif /* serializable_hpp */
