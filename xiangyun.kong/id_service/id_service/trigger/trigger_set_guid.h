//
//  Header.h
//  id_service
//
//  Created by 孔祥云 on 10/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <id_service/id_service.hpp>

#include <plugin/trigger/trigger.h>

#include <errors.h>

using namespace pf;

namespace kxy {
    
    class set_guid : public trigger {
    public:
        DECLARE_TYPE(trigger, TRIGGER_SET_GUID);
        
    public:
        virtual void happen(ptr<plugin> owner, ptr<event> evt) override {
            ptr<id_service> id_service = owner;
            ptr<serializable> params = evt->param();
            
            long guid;
            params >> guid;
            id_service->set_guid(guid);
        }
        
    };
}


#endif /* Header_h */
