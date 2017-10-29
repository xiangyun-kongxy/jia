//
//  ind_response.hpp
//  ps
//
//  Created by xiangyun.kong on 10/28/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef ind_response_h
#define ind_response_h

#include "ps_index.hpp"

#include <lib/lock/spinlock.hpp>

#include <common/identifier/id_response.hpp>

#include <map>

using namespace std;
using namespace kxy;

namespace pf {

    class ind_rsp : public ps_index {
    public:
        virtual list<long> search(ptr<object> obj) override {
            list<long> result;
            fcallback callback = nullptr;

            if (!obj->is_kind_of(OBJ_RESPONSE)) {
                return result;
            }
            
            map<ptr<object>, pair<long, fcallback>>::iterator i;
            ptr<response> rsp = obj;

            m_mutex.lock();

            i = m_registed.find(rsp->org_event());
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
            ptr<id_response> id_rsp = obj;
            
            m_mutex.lock();

            m_registed[id_rsp->event()] = pair<long, fcallback>(slot, nullptr);

            m_mutex.unlock();
        }

        virtual void registe(ptr<object> obj, fcallback callback) override {
            ptr<id_response> id_rsp = obj;
            
            m_mutex.lock();

            m_registed[id_rsp->event()] = pair<long, fcallback>(-1, callback);

            m_mutex.unlock();
        }
        
    private:
        map<ptr<object>, pair<long, fcallback>> m_registed;
        spin_mutex m_mutex;
    };
}

#endif /* ind_response_h */
