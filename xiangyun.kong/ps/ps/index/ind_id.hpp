//
//  ind_id.hpp
//  ps
//
//  Created by xiangyun.kong on 10/28/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef ind_id_h
#define ind_id_h

#include "ps_index.hpp"

#include <lib/lock/spinlock.hpp>

#include <map>

using namespace std;
using namespace kxy;

namespace pf {

    class ind_id : public ps_index {
    public:
        virtual list<long> search(ptr<object> obj) override {
            list<long> result;
            fcallback callback = nullptr;

            map<ptr<object>, pair<long, fcallback>>::iterator i;

            m_mutex.lock();

            i = m_registed.find(obj);
            if (i != m_registed.end()) {
                if (i->second.first >= 0) {
                    result.push_back(i->second.first);
                } else {
                    callback = i->second.second;
                }
                m_registed.erase(i);
            }
            
            m_mutex.unlock();

            if (callback != nullptr) {
                callback(obj);
            }
            return result;
        }

        virtual void registe(ptr<object> obj, long slot) override {
            m_mutex.lock();

            m_registed[obj] = pair<long, fcallback>(slot, nullptr);
            
            m_mutex.unlock();
        }

        virtual void registe(ptr<object> obj, fcallback callback) override {
            m_mutex.lock();

            m_registed[obj] = pair<long, fcallback>(-1, callback);
            
            m_mutex.unlock();
        }

    private:
        map<ptr<object>, pair<long, fcallback>> m_registed;
        spin_mutex m_mutex;
    };
    
}

#endif /* ind_id_h */
