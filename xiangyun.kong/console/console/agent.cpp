//
//  agent.cpp
//  console
//
//  Created by 孔祥云 on 10/29/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "agent.hpp"

#include <map>
#include <iostream>

#include <plugin/manager/plugin_manager.hpp>
#include <plugin/event/simple_event.hpp>

#include <lib/identifier/id_name.hpp>

#include <ipc.hpp>
#include <errors.hpp>

using namespace pf;
using namespace std;

map<string, list<ptr<pf::function>>> g_functions;


void update_functions() {
    plugin_manager* pm = plugin_manager::instance();
    
    map<string, list<ptr<pf::function>>>::iterator i;
    g_functions.clear();
    
    list<ptr<plugin>> plugins = pm->get_all_plugin();
    for (ptr<plugin> pl : plugins) {
        for (ptr<pf::function> func : pl->supported_functions()) {
            i = g_functions.find(func->name());
            if (i != g_functions.end()) {
                i->second.push_back(func);
            } else {
                list<ptr<pf::function>> functions;
                functions.push_back(func);
                g_functions[func->name()] = functions;
            }
        }
    }
}

void show_framework_functions(const string& function_name) {
    update_functions();
    
    map<string, list<ptr<pf::function>>>::iterator i;
    i = g_functions.find(function_name);
    if (i != g_functions.end()) {
        for (ptr<pf::function> func : i->second) {
            printf("    @%-16s:%-20s ", func->provider()->name().c_str(),
                   func->name().c_str());
            for (TYPE ty : func->param_type()) {
                switch (ty) {
                    case pf::T_NONE:
                        printf (" %-7s", "-");
                        break;
                    case pf::T_INT:
                        printf (" %-7s", "integer");
                        break;
                    case pf::T_STR:
                        printf (" %-7s", "string");
                        break;
                    case pf::T_FLOAT:
                        printf (" %-7s", "float");
                        break;
                    case pf::T_USER:
                        printf (" %-7s", "*");
                        break;
                }
            }
            cout << endl;
        }
    } else {
        cout << "function not found §" << function_name << endl;
    }
}

void show_framework_functions() {
    update_functions();
    
    map<string, list<ptr<pf::function>>>::iterator i;
    for (i = g_functions.begin(); i != g_functions.end(); ++i) {
        for (ptr<pf::function> func : i->second) {
            printf("    @%-16s:%-20s ", func->provider()->name().c_str(),
                   func->name().c_str());
            for (TYPE ty : func->param_type()) {
                switch (ty) {
                    case pf::T_NONE:
                        printf (" %-7s", "-");
                        break;
                    case pf::T_INT:
                        printf (" %-7s", "integer");
                        break;
                    case pf::T_STR:
                        printf (" %-7s", "string");
                        break;
                    case pf::T_FLOAT:
                        printf (" %-7s", "float");
                        break;
                    case pf::T_USER:
                        printf (" %-7s", "*");
                        break;
                }
            }
            cout << endl;
        }
    }
}

void call_framework_function(queue<string> cmds) {
    string plugin_name;
    if (cmds.front().at(0) == '@') {
        plugin_name = cmds.front();
        plugin_name.erase(plugin_name.begin());
        cmds.pop();
    }
    
    if (cmds.size() == 0) {
        cout << "error: command missed." << endl;
    }
    
    map<string, list<ptr<pf::function>>>::iterator i;
    i = g_functions.find(cmds.front());
    if (i != g_functions.end()) {
        cmds.pop();
        if (i->second.size() > 1 && plugin_name == "") {
            cout << "error: mulltiple function found."
                    "plugin should be specified" << endl;
        } else {
            for (ptr<pf::function> func : i->second) {
                if (plugin_name == "" ||
                    func->provider()->name() == plugin_name) {
                    ptr<serializable> param = new serializable;
                    for (pf::TYPE ty : func->param_type()) {
                        if (cmds.size() == 0) {
                            cout << "error: parameter missed."
                                    "you can show help for detail." << endl;
                            return;
                        }
                        
                        switch (ty) {
                            case pf::T_INT:
                                param << atol(cmds.front().c_str());
                                break;
                            case pf::T_STR:
                                param << cmds.front();
                                break;
                            case pf::T_FLOAT:
                                param << atof(cmds.front().c_str());
                                break;
                            case pf::T_USER:
                            case pf::T_NONE:
                                cout << "error: parameter type not supported "
                                        "in this function." << endl;
                                return;
                        }
                        cmds.pop();
                    }
                    ptr<event> evt;
                    evt = new simple_event(func->name(), param,
                                           new id_name(func->provider()->name()));
                    if (func->return_type() != T_NONE) {
                        ptr<response> rsp = call(evt);
                        if (rsp == nullptr) {
                            cout << "error: response is null." << endl;
                        } else {
                            if (rsp->code() == EC_OK) {
                                long i_result;
                                string s_result;
                                double f_result;
                                switch (func->return_type()) {
                                    case pf::T_INT:
                                        rsp->context() >> i_result;
                                        cout << i_result << endl;
                                        break;
                                    case pf::T_STR:
                                        rsp->context() >> s_result;
                                        cout << s_result << endl;
                                        break;
                                    case pf::T_FLOAT:
                                        rsp->context() >> f_result;
                                        cout << f_result << endl;
                                        break;
                                    default:
                                        cout << "*" << endl;;
                                }
                            } else {
                                cout << "error: " << rsp->message() << endl;
                            }
                        }
                    } else {
                        send(evt);
                    }
                    return;
                }
            }
            cout << "error: plugin not found. @" << plugin_name << endl;
        }
    } else {
        cout << "error: command not found §" << cmds.front() << endl;
    }
}
