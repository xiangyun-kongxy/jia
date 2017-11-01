//
//  console.cpp
//  console
//
//  Created by 孔祥云 on 12/31/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <queue>

#include "agent.hpp"

#include <loader/loader.hpp>

#include <lib/init/initializer.hpp>

#include <ut.hpp>

using namespace std;

#define MAX_PARAM_COUNT 10
#define MAX_PARAM_LEN   128
    
static void show_global_help() {
    cout << "commands:" << endl;
    cout << "    help | h | ?" << endl;
    cout << "    exit" << endl;
    cout << "    start <config path>" << endl;
    cout << "    test" << endl;
}

static void show_framework_help() {
    cout << "commands:" << endl;
    cout << "    help | h | ? [function]" << endl;
    cout << "    exit | stop" << endl;
    show_framework_functions();
}

static void show_framework_help(const string& function_name) {
    cout << "commands:" << endl;
    cout << "    help | h | ? [function]" << endl;
    cout << "    exit | stop" << endl;
    show_framework_functions(function_name);
}

queue<string> to_array(const char* line) {
    char params[MAX_PARAM_COUNT][MAX_PARAM_LEN];

    int count = sscanf(line, "%s%s%s%s%s%s%s%s%s%s",
           params[0],
           params[1],
           params[2],
           params[3],
           params[4],
           params[5],
           params[6],
           params[7],
           params[8],
           params[9]
           );
    
    queue<string> result;
    for (long i = 0; i < count; ++i) {
        result.push(params[i]);
    }
    
    return result;
}

int main(int argc, char** argv) {
    char cmd[1024];
    bool framework_loaded = false;
    
    show_global_help();
    
    while (true) {
        cout << "> ";
        size_t len = 0;
        char* buf = fgetln(stdin, &len);
        strncpy(cmd, buf, len);
        cmd[len] = 0;
        queue<string> cmds = to_array(cmd);
        
        if (cmds.size() > 0) {
            if (framework_loaded) {
                if (cmds.front() == "exit" || cmds.front() == "stop") {
                    cout << "unloading plugin framework...";
                    pf::loader::unload();
                    cout << "done" << endl;
                    framework_loaded = false;
                } else if (cmds.front() == "?" || cmds.front() == "Help" ||
                           cmds.front() == "h" || cmds.front() == "help" ||
                           cmds.front() == "H" || cmds.front() == "HELP") {
                    if (cmds.size() > 1) {
                        cmds.pop();
                        show_framework_help(cmds.front());
                    } else {
                        show_framework_help();
                    }
                } else {
                    call_framework_function(cmds);
                }
            } else {
                if (cmds.front() == "exit") {
                    kxy::do_cleanup();
                    break;
                } else if (cmds.front() == "?" || cmds.front() == "Help" ||
                           cmds.front() == "h" || cmds.front() == "help" ||
                           cmds.front() == "H" || cmds.front() == "HELP") {
                    show_global_help();
                } else if (cmds.front() == "start") {
                    if (cmds.size() != 2) {
                        cout << "error: §start takes one parameter" << endl;
                    } else {
                        cmds.pop();
                        cout << "plugin framework is starting...";
                        pf::loader::load(cmds.front());
                        cout << "in progress." << endl;
                        framework_loaded = true;
                    }
                } else if (cmds.front() == "test") {
                    run_ut();
                } else {
                    cout << "error: command not found." << endl;
                }
            }
        }
    }
}
