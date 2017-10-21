//
//  kv.cpp
//  lib
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include <stdio.h>
#include "kv_service/kv_service.hpp"

namespace kxy {
    
    
    kv_service* get_kv_service(const string& service_name) {
        kv_service* service = (*g_kv_services)[service_name];
        
        if(service == nullptr) {
            service = new kv_service(service_name);
            (*g_kv_services)[service_name] = service;
        }
        
        return service;
    }
    
    string kv_get(const string& service_name, const string& key) {
        kv_service* service = get_kv_service(service_name);
        return service->get(key);
    }
    
    void kv_put(const string& service_name, const string& key, const string& value) {
        kv_service* service = get_kv_service(service_name);
        service->put(key, value);
    }
    
}
