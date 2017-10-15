//
//  main.cpp
//  ut
//
//  Created by 孔祥云 on 10/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <loader/loader.hpp>
#include <ut/ut.hpp>

using namespace pf;
using namespace std;

int main(int argc, char** argv) {
    string path =   "/Users/kongxiangyun/Documents/project/kxy/xiangyun.kong"
                    "/console/console/config/mind.xml";
    loader* loader = new class loader(path);
    loader->load();
    
    run_ut();
}
