//
//  ut_barren_lock.cpp
//  ut
//
//  Created by 孔祥云 on 10/15/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include <stdio.h>

#include <ut/ut.hpp>

#include <barren/barren.hpp>
#include <barren/util/barren_io.hpp>

#include <predefined_barren.hpp>

#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;
using namespace mind;

long unlock = 0;

void* thread_func_1(void* param) {
    ptr<barren> br = (barren*)param;
    while (unlock != -1) {
        printf("t1: locking %ld\n", br->id());
        br->lock();
        printf("t1: locked %ld\n", br->id());
        sleep(15);
        printf("t1: unlocking %ld\n", br->id());
        br->unlock();
        printf("t1: unlocked %ld\n", br->id());
    }
    printf("t1 end\n");
    return nullptr;
}

void* thread_func_2(void* param) {
    ptr<barren> br = (barren*)param;
    while (unlock != -1) {
        printf("t2: locking %ld\n", br->id());
        br->lock();
        printf("t2: locked %ld\n", br->id());
        while(unlock != 2 && unlock != -1) {
            usleep(100);
        }
        printf("t2: unlocking %ld\n", br->id());
        br->unlock();
        printf("t2: unlocked %ld\n", br->id());
    }
    printf("t2 end\n");
    return nullptr;
}

void* thread_func_3(void* param) {
    ptr<barren> br = (barren*)param;
    while (unlock != -1) {
        printf("t3: locking %ld\n", br->id());
        br->lock();
        printf("t3: locked %ld\n", br->id());
        while(unlock != 3 && unlock != -1) {
            usleep(100);
        }
        printf("t3: unlocking %ld\n", br->id());
        br->unlock();
        printf("t3: unlocked %ld\n", br->id());
    }
    printf("t3 end\n");
    return nullptr;
}

def_ut(ut_barren_lock) {
    ptr<barren> b1 = new barren;
    ptr<barren> b2 = new barren;
    
    pthread_t thread[3];
    pthread_create(thread + 0, nullptr, thread_func_1, *b1);
    pthread_create(thread + 1, nullptr, thread_func_2, *b2);
    pthread_create(thread + 2, nullptr, thread_func_3, *b2);
    
    while (unlock != -1) {
        cin >> unlock;
    }
    
    pthread_join(thread[0], nullptr);
    pthread_join(thread[1], nullptr);
    pthread_join(thread[2], nullptr);
}

