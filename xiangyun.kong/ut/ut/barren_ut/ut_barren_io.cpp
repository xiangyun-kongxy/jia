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

void* write_speed_func(void* param) {
    long count = (long)param;

    long i;
    for (i = 0; i < count; ++i) {
        save_barren(new barren);
    }

    cout << "end   " << time(nullptr) << endl;

    return nullptr;
}

def_ut(ut_barren_w_speed) {
    long count;
    cout << "barren count to read:";
    cin >> count;
    
    cout << "start " << time(nullptr) << endl;
    
    pthread_t threads[8];
    for (long i = 0; i < 4; ++i) {
        pthread_create(threads + i, nullptr, write_speed_func, (void*)count);
    }
    
    for (long i = 0; i < 1; ++i) {
        pthread_join(threads[i], nullptr);
    }
}

void* read_speed_func(void* param) {
    long count = (long)param;
    
    long i;
    for (i = 0; i < count; ++i) {
        ptr<barren> pbr = load_barren(10000056001L + i);
        if (pbr == nullptr) {
            cout << i << "not found." << endl;
        }
    }
    
    cout << "end   " << time(nullptr) << endl;
    
    return nullptr;
}

def_ut(ut_barren_r_speed) {
    long count;
    cout << "barren count to read:";
    cin >> count;

    cout << "start " << time(nullptr) << endl;
    
    pthread_t threads[8];
    for (long i = 0; i < 4; ++i) {
        pthread_create(threads + i, nullptr, read_speed_func, (void*)count);
    }

    for (long i = 0; i < 1; ++i) {
        pthread_join(threads[i], nullptr);
    }
}
