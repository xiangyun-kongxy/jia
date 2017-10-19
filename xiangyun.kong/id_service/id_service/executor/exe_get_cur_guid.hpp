//
//  exe_get_cur_guid.hpp
//  id_service
//
//  Created by 孔祥云 on 10/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_get_cur_guid_h
#define exe_get_cur_guid_h

#include <id_service/id_service.hpp>

#include <plugin/executor/executor.h>
#include <plugin/response/simple_response.h>

#include <errors.h>

using namespace pf;

namespace kxy {
    
    class get_cur_guid : public executor {
    public:
        DECLARE_TYPE(executor, EXE_GET_CUR_GUID);
        
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<task> tsk) override {
            ptr<id_service> id_service = owner;
            ptr<serializable> result = new serializable;
            
            result << id_service->get_guid();
            return new simple_response(tsk, EC_OK, EM_OK, result);
        }
        
    };
}

#endif /* exe_get_cur_guid_h */
