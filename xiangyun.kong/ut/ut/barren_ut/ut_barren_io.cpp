//
//  barren_io.cpp
//  ut
//
//  Created by 孔祥云 on 10/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include <stdio.h>
#include <ut/ut.hpp>

#include <barren/barren.hpp>
#include <barren/util/barren_io.hpp>

#include <predefined_barren.h>

#include <iostream>
#include <time.h>

using namespace std;
using namespace mind;

def_ut(ut_barren_rw) {
    ptr<barren> br = new barren;
    
    ptr<barren> lbr = load_barren(br->id());
    assert(lbr != nullptr);
    
    cout << lbr->id() << " created and loaded" << endl;
}

def_ut(ut_barren_rw_speed) {
    long count;
    cout << "barren count to rw:";
    cin >> count;
    
    long start = time(nullptr);
    long i;
    for (i = 0; i < count; ++i) {
        save_barren(new barren);
    }
    cout << "write " << i << " barrens cost " << time(nullptr) - start << endl;
    
    start = time(nullptr);
    for (i = 0; i < count; ++i) {
        ptr<barren> pbr = load_barren(10000056000L + i);
        assert(pbr != nullptr);
    }
    cout << "read " << i << " barrens cost " << time(nullptr) - start << endl;
}
