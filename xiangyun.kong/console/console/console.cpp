//
//  console.cpp
//  console
//
//  Created by 孔祥云 on 12/31/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <loader/loader.hpp>

using namespace pf;
using namespace std;

static void show_help() {
    cout << "usage:" << endl;
    cout << "    console <plugin_conf>" << endl;
}

int main(int argc, char** argv) {
    if(argc > 1) {
        loader::load(argv[1]);
        while(1) {
            sleep(1);
        }
    } else {
        show_help();
    }
}
