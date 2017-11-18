//
//  predefined_barren.h
//  
//
//  Created by 孔祥云 on 10/14/17.
//
//

#ifndef predefined_barren_h
#define predefined_barren_h

#include <barren/barren.hpp>

static const long BARREN_FALSE              = 0;
static const long BARREN_TRUE               = 1;

namespace mind {

    extern ptr<barren> bfalse;
    extern ptr<barren> btrue;
    
}


static const long BARREN_SYS_BEGIN          = 1e8;
static const long BARREN_SYS_END            = 1e9 - 1;
static const long BARREN_FREE_BEGIN         = 1e9;
static const long BARREN_FREE_END           = 1e18 - 1;

static const long BARREN_IS                 = BARREN_SYS_BEGIN + 0;
static const long BARREN_INFER              = BARREN_SYS_BEGIN + 1;
static const long BARREN_BELONG_TO          = BARREN_SYS_BEGIN + 2;
static const long BARREN_KIND_OF            = BARREN_SYS_BEGIN + 3;
static const long BARREN_NOT                = BARREN_SYS_BEGIN + 4;
static const long BARREN_AND                = BARREN_SYS_BEGIN + 5;
static const long BARREN_OR                 = BARREN_SYS_BEGIN + 6;
static const long BARREN_BARREN             = BARREN_SYS_BEGIN + 7;
static const long BARREN_QUANTITY           = BARREN_SYS_BEGIN + 8;
static const long BARREN_SEQUENCE           = BARREN_SYS_BEGIN + 9;
static const long BARREN_POSITION           = BARREN_SYS_BEGIN + 10;
static const long BARREN_PROBABILITY        = BARREN_SYS_BEGIN + 11;
static const long BARREN_MATCH              = BARREN_SYS_BEGIN + 12;
static const long BARREN_SET                = BARREN_SYS_BEGIN + 13;
static const long BARREN_DIVIDE             = BARREN_SYS_BEGIN + 14;
static const long BARREN_RECURRENCE         = BARREN_SYS_BEGIN + 15;
static const long BARREN_REPLACE            = BARREN_SYS_BEGIN + 16;

static const long BARREN_CALL               = BARREN_SYS_BEGIN + 17;
static const long BARREN_CALL_RESULT        = BARREN_SYS_BEGIN + 18;
static const long BARREN_DEFINE             = BARREN_SYS_BEGIN + 19;
static const long BARREN_FUNCTION           = BARREN_SYS_BEGIN + 20;

static const long BARREN_BSF                = BARREN_SYS_BEGIN + 21;
static const long BARREN_BEF                = BARREN_SYS_BEGIN + 22;

static const long BARREN_MIND               = BARREN_SYS_BEGIN + 1024;
static const long BARREN_QUERY              = BARREN_SYS_BEGIN + 1025;

#endif /* predefined_barren_h */
