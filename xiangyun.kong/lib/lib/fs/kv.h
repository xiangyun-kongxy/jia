//
//  kv.h
//  lib
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef kv_h
#define kv_h


namespace kxy {
    
    string kv_get(const string& service_name, const string& key);
    void kv_put(const string& service_name, const string& key, const string& value);
    
}

#endif /* kv_h */
