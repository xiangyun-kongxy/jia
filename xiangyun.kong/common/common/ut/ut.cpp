//
//  ut.cpp
//  common
//
//  Created by 孔祥云 on 10/29/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#include <unistd.h>
#include <iostream>

#include <ut.hpp>

using namespace std;

map<string, ut_func>* g_ut_list = nullptr;

map<string, ut_func>& get_ut_list() {
    if (g_ut_list == nullptr) {
        g_ut_list = new map<string, ut_func>;
    }
    return *g_ut_list;
}

void show_ut_help() {
    map<string, ut_func>::const_iterator i;
    cout << "cases:" << endl;
    
    for (i = get_ut_list().begin(); i != get_ut_list().end(); ++i) {
        cout << "\t>> " << i->first << endl;
    }
    cout << endl;
    cout << "\t* all" << endl;
    cout << "\t* exit" << endl;
}

void run_ut() {
    show_ut_help();
    
    string cmd;
    cout << "ut to run: ";
    cin >> cmd;
    while (cmd != "exit") {
        map<string, ut_func>::const_iterator i;
        i = get_ut_list().find(cmd);
        if (i != get_ut_list().end()) {
            cout << "running " << i->first << " ..." << endl;
            i->second();
        } else if (cmd == "all") {
            for (i = get_ut_list().begin(); i != get_ut_list().end(); ++i) {
                cout << "running " << i->first << " ..." << endl;
                i->second();
            }
        } else if (cmd == "h" || cmd == "help" || cmd == "?") {
            show_ut_help();
        } else {
            cout << "ut " << cmd << " not found!" << endl;
        }
        cout << "ut to run: ";
        cin >> cmd;
    }
}
