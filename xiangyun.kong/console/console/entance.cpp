//
//  entance.cpp
//  console
//
//  Created by 孔祥云 on 11/4/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include <console/terminal.hpp>

using namespace pf;

int main(int argc, char** argv) {
    ptr<terminal> term = new terminal;
    term->init();
    term->resume();
    
    term->command_loop();
    return 0;
}
