//
//  initializer.cpp
//  lib
//
//  Created by 孔祥云 on 10/21/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "initializer.hpp"

#include <map>
#include <iostream>

using namespace std;

namespace kxy {
    
    map<string, uninit_func>* g_uninit_func_list = nullptr;
    
    void register_uninitializer(const string& name, uninit_func func) {
        if (g_uninit_func_list == nullptr) {
            g_uninit_func_list = new map<string, uninit_func>;
        }
        (*g_uninit_func_list)[name] = func;
    }
    
    void do_cleanup() {
        map<string, uninit_func>::iterator i;
        for (i = g_uninit_func_list->begin(); i != g_uninit_func_list->end(); ++i) {
            cout << "doing " << i->first << "..." << endl;
            i->second();
        }
    }
    
}
