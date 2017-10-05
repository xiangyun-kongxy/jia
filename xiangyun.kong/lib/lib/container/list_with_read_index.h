//
//  list_with_read_index.h
//  lib
//
//  Created by 孔祥云 on 1/22/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef list_with_read_index_h
#define list_with_read_index_h

#include <list>
#include <cstdlib>

using namespace std;

namespace kxy {
    
#define LWRI_MAX_INDEX_SIZE     4
#define LWRI_ACTION_ADD         1
#define LWRI_ACTION_RM          0
    
    template<typename ty>
    class list_with_read_index {
    public:
        typedef ty value_type;
        typedef list<value_type> container_type;
        typedef typename container_type::iterator iterator;
        
        typedef list_with_read_index<value_type> this_type;
        
    private:
        typedef pair<long, iterator> index_value_type;
        typedef list<index_value_type> index_type;
        typedef typename index_type::iterator index_iterator;
        
    public:
        list_with_read_index() {
        }
        
    public:
        long size() const {
            return m_container.size();
        }
        
        value_type at(long pos) const {
            iterator i = ((this_type*)this)->get_pos(pos);
            if(i == m_container.end()) {
                return value_type();
            } else {
                return *i;
            }
        }
        
        void remove(long pos) {
            iterator i = get_pos(pos);
            m_container.erase(i);
            update_index(LWRI_ACTION_RM, pos);
        }
        
        void add(const value_type& value) {
            m_container.push_back(value);
            m_index_cur.first = m_container.size() - 1;
            m_index_cur.second = --m_container.end();
        }
        
        void insert(long pos, const value_type& id) {
            iterator i = get_pos(pos);
            m_container.insert(i, id);
            update_index(LWRI_ACTION_ADD, pos);
        }
        
        void change_pos(long org, long latest) {
            iterator i = get_pos(org);
            value_type value = *i;
            remove(org);
            insert(latest, value);
        }
        
        void change_value(long pos, const string& value) {
            iterator i = get_pos(pos);
            *i = value;
        }
        
        void swap(long first, long second) {
            iterator ifirst = get_pos(first);
            iterator isecond = get_pos(second);
            
            value_type tmp = *ifirst;
            *ifirst = *isecond;
            *isecond = tmp;
        }
        
    private:
        iterator get_pos(long pos) {
            index_value_type ip = get_near_pos(pos);
            iterator i;
            long diff;
            long distance;
            
            i = ip.second;
            distance = pos - ip.first;
            
            diff = labs(distance);
            
            if(distance > 0) {
                while(distance > 0) {
                    --distance;
                    ++i;
                }
            } else if(distance < 0) {
                while(distance < 0) {
                    ++distance;
                    --i;
                }
            }
            
            if(m_index.size() < LWRI_MAX_INDEX_SIZE ||
               m_container.size() > LWRI_MAX_INDEX_SIZE * 2 * diff) {
                add_index(pos, i);
            }
            
            return i;
        }
        
        index_value_type get_near_pos(long pos) {
            index_value_type cur = m_index_cur;
            
            for(index_iterator i = m_index.begin(); i != m_index.end(); ++i) {
                if(labs(i->first - pos) < labs(cur.first - pos)) {
                    cur = *i;
                }
            }
            
            m_index_cur = cur;
            return cur;
        }
        
        void update_index(long action, long pos) {
            void (this_type::*updater)(long, index_iterator);
            updater = get_updater(action);
            
            index_iterator i;
            for(i = m_index.begin(); i != m_index.end(); ) {
                (this->*updater)(pos, i++);
            }
        }
        
        void (this_type::*get_updater(long action))(long, index_iterator) {
            switch(action) {
                case LWRI_ACTION_RM:
                    return &this_type::update_index_shift_left;
                case LWRI_ACTION_ADD:
                    return &this_type::update_index_shift_right;
            }
            return nullptr;
        }
        
        void update_index_shift_right(long pos, index_iterator i) {
            if(i->first >= pos) {
                ++i->first;
            }
        }
        
        void update_index_shift_left(long pos, index_iterator i) {
            if(i->first == pos) {
                m_index.erase(i);
            } else if(i->first > pos) {
                --i->first;
            }
        }
        
        void add_index(long pos, iterator i) {
            if(m_index.size() >= LWRI_MAX_INDEX_SIZE) {
                m_index.pop_front();
            }
            m_index.push_back(index_value_type(pos,i));
        }
        
    private:
        container_type m_container;
        index_type m_index;
        index_value_type m_index_cur;
    };
    
}

#endif /* list_with_read_index_h */
