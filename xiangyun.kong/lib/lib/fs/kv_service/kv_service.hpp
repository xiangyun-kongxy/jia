//
//  kv_service.hpp
//  lib
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef kv_service_hpp
#define kv_service_hpp

#include <string>
#include <map>
#include <leveldb/db.h>

using namespace std;
using namespace leveldb;

namespace kxy {
    
    class kv_service {
    public:
        kv_service(const string& name);
        virtual ~kv_service();
        
    public:
        string service_name() const ;
        
    public:
        string get(const string& key);
        void put(const string& key, const string& value);
        
    protected:
        string m_name;
        DB* m_db;
        WriteOptions m_wopt;
        ReadOptions m_ropt;
    };
    
    extern map<string, kv_service*>* g_kv_services;
}

#endif /* kv_service_hpp */
