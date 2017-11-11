//
//  barren_call.cpp
//  executor
//
//  Created by 孔祥云 on 11/9/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#include "barren_call.hpp"
#include "barren_function.hpp"

#include <barren/util/barren_io.hpp>

#include <predefined_barren.hpp>

namespace mind {
    
    ptr<barren> barren_call::call() {
        ptr<barren> result;
        
        if (is_call()) {
            deque<ptr<barren>> params;
            for (long i = 3; i < size(); ++i) {
                if ((*this)[i] > 0) {
                    params.push_back(load_barren((*this)[i]));
                } else if ((*this)[i] <= 0) {
                    params.push_back(nullptr);
                }
            }
            result = call(params);
        } else  {
            result = this;
        }
        
        return result;
    }
    
    ptr<barren> barren_call::call(const deque<ptr<mind::barren> > &params) {
        if (!is_call()) {
            return this;
        }
        
        ptr<barren_function> sub_func = load_barren((*this)[2]);
        if (sub_func != nullptr) {
            ptr<barren_call> call = sub_func;
            if (call->is_call()) {
                sub_func = call->call(params);
            }
        }
        
        if (sub_func == nullptr) {
            return load_barren(0L);
        } else if (!sub_func->is_function()) {
            return sub_func;
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
                ptr<barren_call> sub_call = load_barren((*this)[i-3]);
                if (sub_call != nullptr) {
                    local_params.push_back(sub_call->call(params));
                } else {
                    local_params.push_back(load_barren(0L));
                }
            }
        }

        bfunction  func = sub_func->get_raw_function();
        if (func != nullptr) {
            ptr<barren_call> result = func(local_params);
            if (result->is_call()) {
                return result->call(params);
            } else {
                return result;
            }
        } else {
            return load_barren(0L);
        }
    }
    
    bool barren_call::is_call() const {
        return size() >= 3 && (*(barren_call*)this)[1L] == BARREN_CALL;
    }
}
