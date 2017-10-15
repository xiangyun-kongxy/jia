//
//  exe_fetch_add_guid.h
//  id_service
//
//  Created by 孔祥云 on 10/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_fetch_add_guid_h
#define exe_fetch_add_guid_h

#include "../id_service.hpp"

#include <executor/executor.h>
#include <response/simple_response.h>
#include <errors.h>
#include <names.h>


using namespace pf;

namespace kxy {
    
    class fetch_add_guid : public executor {
    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<task> tsk) override {
            ptr<id_service> id_service = owner;
            ptr<serializable> result = new serializable;
            
            result << id_service->fetch_add_guid();
            return new simple_response(EC_OK, EM_OK, result);
        }
            
        virtual string type() const override {
            return EXE_FETCH_ADD_GUID;
        }
            
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == EXE_FETCH_ADD_GUID || executor::is_kind_of(type_name);
        }
    };
}

#endif /* exe_fetch_add_guid_h */
