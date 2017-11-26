//
//  bsp_pp_parser.cpp
//  spl
//
//  Created by 孔祥云 on 11/21/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "bsp_pp_parser.hpp"

#include <spl/bsp/lexical/types/bsp_pp_keywork.hpp>
#include <spl/bsp/lexical/types/bsp_pp_string.hpp>
#include <spl/bsp/lexical/types/bsp_pp_number.hpp>
#include <spl/bsp/lexical/types/bsp_pp_symbol.hpp>
#include <spl/bsp/lexical/types/bsp_pp_op.hpp>
#include <spl/bsp/lexical/types/bsp_pp_comment.hpp>


namespace spl {
namespace bsp {
    
    bsp_pp_parser::parser bsp_pp_parser::m_parser_map[256];
    
    deque<ptr<pptoken>> bsp_pp_parser::parse(ptr<lfile> pfile) {
        deque<ptr<pptoken>> tokens;
        
        _init();
        
        ptr<llocation> location = new llocation(pfile, 1, 1, nullptr);
        while (pfile->source_code()[location->pos()] != 0) {
            parser parser = _get_parser(location);
            ptr<pptoken> token = parser(location);
            if (token != nullptr) {
                tokens.push_back(token);
            }
        }
        
        return tokens;
    }
    
    void bsp_pp_parser::_init() {
        for (int i = 0; i < 256; ++i) {
            m_parser_map[i] = _p_parse_err_char;
        }
        
        m_parser_map[(unsigned)'#'] = _p_parse_keywork;
        
        m_parser_map[(unsigned)'"'] = _p_parse_string;
        
        m_parser_map[(unsigned)'-'] = _p_parse_number;
        m_parser_map[(unsigned)'0'] = _p_parse_number;
        m_parser_map[(unsigned)'1'] = _p_parse_number;
        m_parser_map[(unsigned)'2'] = _p_parse_number;
        m_parser_map[(unsigned)'3'] = _p_parse_number;
        m_parser_map[(unsigned)'4'] = _p_parse_number;
        m_parser_map[(unsigned)'5'] = _p_parse_number;
        m_parser_map[(unsigned)'6'] = _p_parse_number;
        m_parser_map[(unsigned)'7'] = _p_parse_number;
        m_parser_map[(unsigned)'8'] = _p_parse_number;
        m_parser_map[(unsigned)'9'] = _p_parse_number;
        
        m_parser_map[(unsigned)'('] = _p_parse_op;
        m_parser_map[(unsigned)')'] = _p_parse_op;
        m_parser_map[(unsigned)','] = _p_parse_op;
        
        m_parser_map[(unsigned)'/'] = _p_parse_comment;
        
        m_parser_map[(unsigned)' '] = _p_parse_space;
        m_parser_map[(unsigned)'\t'] = _p_parse_space;
        m_parser_map[(unsigned)'\n'] = _p_parse_space;
        m_parser_map[(unsigned)'\r'] = _p_parse_space;
        
        m_parser_map[(unsigned)'_'] = _p_parse_symbol;
        for (int i = 'a'; i < 'z'; ++i) {
            m_parser_map[i] = _p_parse_symbol;
        }
        for (int i = 'A'; i < 'Z'; ++i) {
            m_parser_map[i] = _p_parse_symbol;
        }
    }
    
    ptr<pptoken> bsp_pp_parser::_p_parse_keywork(ptr<llocation> location) {
        ptr<pptoken> token;
        
        char* source = location->file()->source_code();
        if (0 != strncmp(source + location->pos(), "#include", 8)) {
            // error
            location->pos() += 1;
        } else {
            ptr<llocation> ll = location->dup();
            token = new bsp_pp_keywork("#include", ll);
            
            location->column() += 8;
            location->pos() += 8;
        }
        
        return token;
    }
    
    ptr<pptoken> bsp_pp_parser::_p_parse_string(ptr<spl::llocation> location) {
        ptr<pptoken> token;
        
        char* source = location->file()->source_code() + location->pos();
        char* p = source + 1;
        while (*p != '"' && *p != '\n' && *p != 0)
            ++p;
        if (*p != '"') {
            if (*p == '\n') {
                ++location->line();
                location->column() = 1;
                location->pos() += p - source + 1;
            }
            // error
        } else {
            *p = 0;
        
            ptr<llocation> ll = location->dup();
            ++ll->column();
            token = new bsp_pp_string(source+1, ll);
        
            location->column() += p - source + 1;
            location->pos() += p - source + 1;
        }
        
        return token;
    }
    
}
}
