//
//  kv_service.cpp
//  lib
//
//  Created by 孔祥云 on 1/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "kv_service.hpp"

#include <lib/init/initializer.hpp>

#include <iostream>

using namespace std;

namespace kxy {
    
    map<string, kv_service*>* g_kv_services = nullptr;
    
    void __uninit_kv_service() {
        map<string, kv_service*>::iterator i;
        for (i = g_kv_services->begin(); i != g_kv_services->end(); ++i) {
            delete i->second;
        }
        g_kv_services->clear();
        delete g_kv_services;
        g_kv_services = nullptr;
    }
    
    void __attribute__((constructor)) __init_kv_service() {
        g_kv_services = new map<string, kv_service*>;
        
        register_uninitializer("uninitialize kv service", __uninit_kv_service);
    }
    
    kv_service::kv_service(const string& name) {
        m_name = name;
        Options opt;
        opt.create_if_missing = true;
        Status status = DB::Open(opt, "/mind/leveldb/" + m_name, &m_db);
        if (!status.ok()) {
            cout << "leveldb: " << status.ToString() << endl;
        }
    }
    
    kv_service::~kv_service() {
        delete m_db;
    }
    
    string kv_service::service_name() const {
        return m_name;
    }
    
    string kv_service::get(const string &key) {
        string config="";
        if (m_db != nullptr) {
            Status status = m_db->Get(m_ropt, key, &config);
            if (!status.ok()) {
                cout << "leveldb: " << status.ToString() << endl;
            }
        }
        return config;
    }
    
    void kv_service::put(const string &key, const string &value) {
        if (m_db != nullptr) {
            Status status = m_db->Put(m_wopt, key, value);
            if (!status.ok()) {
                cout << "leveldb: " << status.ToString() << endl;
            }
        }
    }
    
}
