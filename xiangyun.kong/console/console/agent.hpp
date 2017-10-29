//
//  agent.hpp
//  console
//
//  Created by 孔祥云 on 10/29/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef agent_hpp
#define agent_hpp

#include <string>
#include <queue>

using namespace std;

void show_framework_functions();
void show_framework_functions(const string& function_name);

void call_framework_function(queue<string> cmd);

#endif /* agent_hpp */
