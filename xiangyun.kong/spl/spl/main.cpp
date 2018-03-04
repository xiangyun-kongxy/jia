//
//  main.cpp
//  spl
//
//  Created by 孔祥云 on 3/22/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include <iostream>
#include <string>
#include <regex>

#include <spl/bsp/bsp_complier.hpp>

using namespace std;
using namespace spl;

void test_regex() {
    try {
        string ppstr = "(\")(?:[^\"\\\\]|\\\\.)*\"";
        string ppchar = "(')(?:[^'\\\\]|\\\\.)'";
        string ppint = "0(x)[0-9a-fA-F]{1,16}|(0)[0-7]{0,22}|([1-9])[0-9]{0,20}";
        regex pattern(ppstr + "|" + ppchar + "|" + ppint, regex::optimize);
        smatch sm;
        regex_match(string("'0'"), sm, pattern);
        cout << sm.size() << endl;
        for(int i = 0; i < sm.size(); ++i) {
            cout << sm[i] << endl;
        }
    } catch (exception e) {
        cout << e.what() << endl;
    }
}

int main(int argc, const char * argv[]) {
    bsp::compiler compiler;
    compiler.add_dir("/Users/kongxiangyun/Documents/project/kxy/xiangyun.kong/bsp/mind");
    compiler.compile();
    compiler.show_barren();
    return 0;
}
