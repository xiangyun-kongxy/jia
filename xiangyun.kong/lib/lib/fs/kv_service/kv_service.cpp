//
//  kv_service.cpp
//  lib
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "kv_service.hpp"

#include <iostream>

using namespace std;

namespace kxy {
    
    map<string, kv_service*> g_kv_services;
    
    kv_service::kv_service(const string& name) {
        m_name = name;
        Options opt;
        opt.create_if_missing = true;
        Status status = DB::Open(opt, "/leveldb/data/" + m_name, &m_db);
        if (!status.ok()) {
            string info = status.ToString();
            cout << info << endl;
        }
    }
    
    kv_service::~kv_service() {
        delete m_db;
    }
    
    string kv_service::service_name() const {
        return m_name;
    }
    
    string kv_service::get(const string &key) {
        string config;
        m_db->Get(m_ropt, key, &config);
        return config;
    }
    
    void kv_service::put(const string &key, const string &value) {
        m_db->Put(m_wopt, key, value);
    }
    
}
