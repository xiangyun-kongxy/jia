//
//  ind_seq.hpp
//  ps
//
//  Created by xiangyun.kong on 10/28/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef ind_seq_h
#define ind_seq_h

#include "ps_index.hpp"

#include <mutex>

using namespace std;

namespace pf {

    class ind_seq : public ps_index {
    private:
        struct context {
            ptr<identifier> cond;
            long slot;
            fcallback callback;
        };
        
    public:
        virtual list<long> search(ptr<object> obj) override {
            list<long> result;
            list<fcallback> callbacks;

            list<context>::iterator i;
            m_mutex.lock();

            for (i = m_registed.begin(); i != m_registed.end(); ++i) {
                if (i->cond->match(obj)) {
                    if (i->slot >= 0) {
                        result.push_back(i->slot);
                    } else if (i->callback != nullptr) {
                        callbacks.push_back(i->callback);
                    }
                }
            }

            m_mutex.unlock();

            for (fcallback callback : callbacks) {
                callback(obj);
            }

            return result;
        }

        virtual void registe(ptr<object> obj, long slot) override {
            context ctt = {obj, slot, nullptr};
            
            m_mutex.lock();
            m_registed.push_back(ctt);
            m_mutex.unlock();
        }

        virtual void registe(ptr<object> obj, fcallback callback) override {
            context ctt = {obj, -1, callback};
            
            m_mutex.lock();
            m_registed.push_back(ctt);
            m_mutex.unlock();
        }

    private:
        list<context> m_registed;
        mutex m_mutex;
    };
    
}

#endif /* ind_seq_h */
