//
//  pp_parser.hpp
//  spl
//
//  Created by 孔祥云 on 11/19/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef pp_parser_h
#define pp_parser_h

#include <spl/general/pptoken.hpp>
#include <spl/general/llocation.hpp>

namespace spl {
    
    class pp_parser {
    public:
        virtual ptr<pptoken> parse(ptr<llocation> loc) = 0;
    };
    
}

#endif /* pp_parser_h */
