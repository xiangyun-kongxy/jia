//
//  exe_fetch_add_guid.h
//  id_service
//
//  Created by 孔祥云 on 10/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_fetch_add_guid_h
#define exe_fetch_add_guid_h

#include <id_service/id_service.hpp>

#include <plugin/executor/executor.h>
#include <plugin/response/simple_response.h>

#include <errors.h>
#include <names.h>


using namespace pf;

namespace kxy {
    
    class fetch_add_guid : public executor {
    public:
        DECLARE_TYPE(executor, EXE_FETCH_ADD_GUID);
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<id_service> id_service = owner;
            ptr<serializable> result = new serializable;
            
            result << id_service->fetch_add_guid();
            return new simple_response(evt, EC_OK, EM_OK, result);
        }
            
    };
}

#endif /* exe_fetch_add_guid_h */
