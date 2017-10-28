//
//  deliver_manager.hpp
//  bus
//
//  Created by 孔祥云 on 10/26/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef deliver_manager_h
#define deliver_manager_h

#include <bus/schedule/object_deliver/deliver.hpp>

#include <bus/schedule/object_deliver/dlv_response.hpp>
#include <bus/schedule/object_deliver/dlv_sequence.hpp>


#include <ipc.hpp>

namespace pf {
    
    class deliver_manager : public deliver {
    public:
        deliver_manager() {
            m_default_deliver = new dlv_sequence;
            
            m_delivers[OBJ_RESPONSE] = new dlv_response;
        }
        
        virtual ~deliver_manager() {
            delete m_default_deliver;
            
            map<string, deliver*>::iterator i;
            for (i = m_delivers.begin(); i != m_delivers.end(); ++i) {
                delete i->second;
            }
        }
        
    public:
        virtual void delive(ptr<object> what) override {
            deliver* dlv = _select_deliver(what);
            dlv->delive(what);
        }
        
        virtual void delive(ptr<object> what, fcallback func) override {
            deliver* dlv = _select_deliver(what);
            dlv->delive(what, func);
        }
        
        virtual void schedule(ptr<object> obj) override {
            deliver* dlv = _select_deliver(obj);
            dlv->schedule(obj);
        }
        
    private:
        deliver* _select_deliver(ptr<object> obj) {
            deliver* dlv = m_delivers[obj->type()];
            if (dlv == nullptr) {
                dlv = m_default_deliver;
            }
            return dlv;
        }
        
    private:
        map<string, deliver*> m_delivers;
        deliver* m_default_deliver;
    };
    
}

#endif /* deliver_manager_h */
