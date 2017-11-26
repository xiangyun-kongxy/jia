//
//  bsp_pp_parser.hpp
//  spl
//
//  Created by 孔祥云 on 11/21/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef bsp_pp_parser_hpp
#define bsp_pp_parser_hpp

#include <spl/general/pptoken.hpp>
#include <spl/general/lfile.hpp>
#include <spl/general/llocation.hpp>

#include <deque>

using namespace std;

namespace spl {
namespace bsp {
    
    class bsp_pp_parser {
    public:
        static deque<ptr<pptoken>> parse(ptr<lfile> pfile);
        
    private:
        typedef ptr<pptoken> (*parser)(ptr<llocation>);
        
    private:
        static ptr<pptoken> _p_parse_keywork(ptr<llocation> location);
        static ptr<pptoken> _p_parse_string(ptr<llocation> location);
        static ptr<pptoken> _p_parse_number(ptr<llocation> location);
        static ptr<pptoken> _p_parse_symbol(ptr<llocation> location);
        static ptr<pptoken> _p_parse_op(ptr<llocation> location);
        static ptr<pptoken> _p_parse_comment(ptr<llocation> location);
        static ptr<pptoken> _p_parse_space(ptr<llocation> location);
        static ptr<pptoken> _p_parse_err_char(ptr<llocation> location);
        
    private:
        static void _init();
        static parser _get_parser(ptr<llocation> location);
        
    private:
        static parser m_parser_map[256];
    };
    
}
}

#endif /* bsp_pp_parser_hpp */
