//
//  Header.h
//  id_service
//
//  Created by 孔祥云 on 10/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef Header_h
#define Header_h


#include <trigger/trigger.h>
#include <errors.h>
#include "../id_service.hpp"

using namespace pf;

namespace kxy {
    
    class set_guid : public trigger {
    public:
        virtual void occur(ptr<plugin> owner, ptr<event> evt) override {
            ptr<id_service> id_service = owner;
            ptr<serializable> params = evt->param();
            
            long guid;
            params >> guid;
            id_service->set_guid(guid);
        }
        
        virtual string type() const override {
            return TRIGGER_SET_GUID;
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == TRIGGER_SET_GUID || trigger::is_kind_of(type_name);
        }
    };
}


#endif /* Header_h */
