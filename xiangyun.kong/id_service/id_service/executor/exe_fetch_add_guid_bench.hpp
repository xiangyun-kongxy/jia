//
//  exe_fetch_add_guid_bench.hpp
//  id_service
//
//  Created by xiangyun.kong on 10/21/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef exe_fetch_add_guid_bench_h
#define exe_fetch_add_guid_bench_h


#include <id_service/id_service.hpp>

#include <plugin/executor/executor.h>
#include <plugin/response/simple_response.h>

#include <errors.h>
#include <names.h>


using namespace pf;

namespace kxy {

    class fetch_add_guid_bench : public executor {
    public:
        DECLARE_TYPE(executor, EXE_FETCH_ADD_GUID_BENCH);

    public:
        virtual ptr<response> run(ptr<plugin> owner, ptr<event> evt) override {
            ptr<id_service> id_service = owner;
            ptr<serializable> param = evt->param();

            long size = 0;
            param >> size;
            
            ptr<serializable> result = new serializable;

            result << id_service->fetch_add_guid(size);
            return new simple_response(evt, EC_OK, EM_OK, result);
        }

    };
}


#endif /* exe_fetch_add_guid_bench_h */
