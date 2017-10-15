//
//  ut.hpp
//  ut
//
//  Created by 孔祥云 on 10/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef ut_hpp
#define ut_hpp

#include <stdio.h>
#include <map>
#include <string>

using namespace std;

typedef void (*ut_func)();

void run_ut();

#define def_ut(ut_name)                                         \
    void ut_name();                                             \
    map<string, ut_func>& get_ut_list();                        \
    void __attribute__((constructor)) __init_ut_##ut_name() {   \
        get_ut_list()[#ut_name] = ut_name;                      \
    }                                                           \
    void ut_name()

#endif /* ut_hpp */
