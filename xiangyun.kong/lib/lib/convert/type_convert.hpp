//
//  basic_type_convert.h
//  lib
//
//  Created by 孔祥云 on 3/14/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef basic_type_convert_h
#define basic_type_convert_h

#include <string>

using namespace std;

namespace kxy {
    
    static const char* SS0 = "\00";
    static const char* SS1 = "\01";
    static const char  CS0 = '\00';
    static const char  CS1 = '\01';
    
    static inline string l2s(unsigned long num) {
        /**
         * 16 numbers are reserved. they are:
         * 0: string terminal
         * 1: objects separate
         * 2: objects separate
         * 3~14: reserved
         * 15(first char of string): string is compressed
         */
        unsigned char buf[9];
        int pos = 0;
        while(num > 0) {
            buf[pos] = num % 240 + 16;
            num /= 240;
            ++pos;
        }
        buf[pos] = CS0;
        return (char*)buf;
    }
    
    static inline long s2l(const char* str) {
        const char *ptr = str + strlen(str) - 1;
        
        long result = 0L;
        while(ptr >= str) {
            result *= 240;
            result += *(const unsigned char*)ptr - 16;
            --ptr;
        }
        
        return result;
    }
    
    static inline long s2l(const char* start, const char* end) {
        const char *ptr = end;
        
        long result = 0L;
        while(ptr >= start) {
            result *= 240;
            result += *(const unsigned char*)ptr - 16;
            --ptr;
        }
        
        return result;
    }
    
}

#endif /* basic_type_convert_h */
