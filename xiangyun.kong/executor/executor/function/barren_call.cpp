//
//  barren_call.cpp
//  executor
//
//  Created by 孔祥云 on 11/9/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#include "barren_call.hpp"
#include <barren/util/barren_io.hpp>

#include <predefined_barren.hpp>

namespace mind {
    
    map<long, bfunction> g_bfunctions;
    
    ptr<barren> barren_call::call(const deque<ptr<mind::barren> > &params) {
        if (!is_call()) {
            return this;
        }
        
        bfunction func;
        ptr<barren_call> sub_func = load_barren((*this)[2]);
        if (sub_func != nullptr) {
            ptr<barren> gf = sub_func->call(params);
            
            if (true) {
                func = g_bfunctions[gf->id()];
            } else {
                return gf;
            }
        } else {
            return load_barren(0L);
        }
        
        deque<ptr<barren>> local_params;
        for (long i = 3; i < size(); ++i) {
            if ((*this)[i-3] < 0) {
                if (params.size() >= i-2) {
                    local_params.push_back(params[i-3]);
                } else {
                    local_params.push_back(load_barren(0L));
                }
            } else if ((*this)[i-3] == 0) {
                local_params.push_back(load_barren(0L));
            } else {
                ptr<barren> obj = load_barren((*this)[i-3]);
                if (obj != nullptr) {
                    ptr<barren_call> sub_call = obj;
                    local_params.push_back(sub_call->call(params));
                } else {
                    local_params.push_back(load_barren(0L));
                }
            }
        }

        ptr<barren_call> result = func(local_params);
        if (result->is_call()) {
            return result->call(params);
        } else {
            return result;
        }
    }
    
    bool barren_call::is_call() const {
        return size() >= 3 && (*(barren_call*)this)[1L] == BARREN_CALL;
    }
}
