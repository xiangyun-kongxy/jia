//
//  macro_overload.h
//  lib
//
//  Created by 孔祥云 on 7/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef macro_overload_h
#define macro_overload_h

#define ARG_N(_1,_2,_3,_4,_5,_6,_7_,_8,_9,_10,_11,_12,_13,_14,_15,_16,N,...)    N
#define COUNT(...) ARG_N(__VA_ARGS__,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

#define CALL_1_1(func,para)         func(para)
#define CALL_1_2(func,para,...)     func(para) CALL_1_1(func, __VA_ARGS__)
#define CALL_1_3(func,para,...)     func(para) CALL_1_2(func, __VA_ARGS__)
#define CALL_1_4(func,para,...)     func(para) CALL_1_3(func, __VA_ARGS__)
#define CALL_1_5(func,para,...)     func(para) CALL_1_4(func, __VA_ARGS__)
#define CALL_1_6(func,para,...)     func(para) CALL_1_5(func, __VA_ARGS__)
#define CALL_1_7(func,para,...)     func(para) CALL_1_6(func, __VA_ARGS__)
#define CALL_1_8(func,para,...)     func(para) CALL_1_7(func, __VA_ARGS__)
#define CALL_1_9(func,para,...)     func(para) CALL_1_8(func, __VA_ARGS__)
#define CALL_1_10(func,para,...)    func(para) CALL_1_9(func, __VA_ARGS__)
#define CALL_1_11(func,para,...)    func(para) CALL_1_10(func, __VA_ARGS__)
#define CALL_1_12(func,para,...)    func(para) CALL_1_11(func, __VA_ARGS__)
#define CALL_1_13(func,para,...)    func(para) CALL_1_12(func, __VA_ARGS__)
#define CALL_1_14(func,para,...)    func(para) CALL_1_13(func, __VA_ARGS__)
#define CALL_1_15(func,para,...)    func(para) CALL_1_14(func, __VA_ARGS__)
#define CALL_1_16(func,para,...)    func(para) CALL_1_15(func, __VA_ARGS__)

#define CAT_RAW(firest, second)     first ## second
#define CAT_INNER(x)                CAT_RAW ##x
#define CAT(first,second)           CAT_INNER((first,second))
#define FOR_EACH_1(func, ...)       CAT(CALL_1_, COUNT(__VA_ARGS__))(func,__VA_ARGS__)

#endif /* macro_overload_h */
