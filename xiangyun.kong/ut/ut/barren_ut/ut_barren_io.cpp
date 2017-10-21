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
    save_barren(br);
    
    ptr<barren> lbr = load_barren(br->id());
    assert(lbr != nullptr);
    
    cout << lbr->id() << " created and loaded" << endl;
}

void* speed_func(void* param) {
    long count = (long)param;

    long i;
    for (i = 0; i < count; ++i) {
        save_barren(new barren);
    }

    for (i = 0; i < count; ++i) {
        ptr<barren> pbr = load_barren(10000056000L + i);
        assert(pbr != nullptr);
    }

    cout << "end   " << time(nullptr) << endl;

    return nullptr;
}

def_ut(ut_barren_rw_speed) {
    long count;
    cout << "barren count to rw:";
    cin >> count;

    cout << "start " << time(nullptr) << endl;
    
    pthread_t threads[8];
    for (long i = 0; i < 1; ++i) {
        pthread_create(threads + i, nullptr, speed_func, (void*)count);
    }

    for (long i = 0; i < 1; ++i) {
        pthread_join(threads[i], nullptr);
    }
}
