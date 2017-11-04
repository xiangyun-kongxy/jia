//
//  termial.cpp
//  console
//
//  Created by 孔祥云 on 11/4/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "terminal.hpp"

#include <iostream>

#include <ipc.hpp>
#include <errors.hpp>

#include <plugin/event/simple_event.hpp>
#include <plugin/manager/plugin_manager.hpp>

#include <lib/identifier/id_name.hpp>

#include <console/executors/help.hpp>
#include <console/executors/start.hpp>
#include <console/executors/stop.hpp>
#include <console/executors/run_cmd.hpp>

using namespace std;
using namespace kxy;

namespace pf {
    
    terminal::terminal() {
        m_executors["?"] = new help;
        m_executors["h"] = new help;
        m_executors["H"] = new help;
        m_executors["help"] = new help;
        m_executors["Help"] = new help;
        m_executors["start"] = new start;
        m_executors["stop"] = new stop;
        m_executors["exit"] = new stop;
        m_executors["run_cmd"] = new run_cmd;
    }
    
    ptr<response> terminal::do_task(ptr<event> evt) {
        plugin::do_task(evt);
        return nullptr;
    }
    
    void terminal::command_loop() {
        while (true) {
            cout << "> ";
            list<string> cmds = _get_cmd();
            
            if (cmds.size() > 0) {
                if ((cmds.front() == "stop" || cmds.front() == "exit") &&
                    m_status["framework"] != "loaded") {
                    
                    uninit();
                    kxy::do_cleanup();
                    break;
                } else {
                    ptr<serializable> param = new serializable;
                    param << cmds;
                    ptr<event> evt = new simple_event("run_cmd", param);
                    tasks()->push(evt);
                }
            }
        }
    }
    
    string& terminal::operator[](const string &key) {
        return m_status[key];
    }
    
    list<string> terminal::_get_cmd() {
        list<string> result;
        char buf[1024];
        int ptr = 0;
        bool in_str = false;
        
        int c;
        do {
            c = getchar();
            if (c > 128) {
                continue;
            }
            
            switch (c) {
                case ' ':
                case '\t':
                case '\n':
                case '\r':
                    if (in_str) {
                        buf[ptr++] = c;
                    } else if (ptr > 0) {
                        buf[ptr] = 0;
                        result.push_back(buf);
                        ptr = 0;
                    }
                    break;
                case '"':
                    if (in_str) {
                        if (ptr > 0) {
                            buf[ptr] = 0;
                            result.push_back(buf);
                            ptr = 0;
                        }
                        in_str = false;
                    } else {
                        in_str = true;
                    }
                    break;
                case '\\':
                    buf[ptr++] = fgetc(stdin);
                    break;
                default:
                    buf[ptr++] = c;
                    break;
            }
        } while(c != '\n' && c != '\r');
        
        return result;
    }
    
    void terminal::call_function(list<string> cmds) {
        _update_functions();
        
        string plugin_name;
        if (cmds.front().at(0) == '@') {
            plugin_name = cmds.front();
            plugin_name.erase(plugin_name.begin());
            cmds.pop_front();
        }
        
        if (cmds.size() == 0) {
            cout << "error: command missed." << endl;
        }
        
        map<string, list<ptr<pf::function>>>::iterator i;
        i = m_functions.find(cmds.front());
        if (i != m_functions.end()) {
            cmds.pop_front();
            if (i->second.size() > 1 && plugin_name == "") {
                cout << "error: multi-function found."
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
                            cmds.pop_front();
                        }
                        ptr<event> evt;
                        evt = new simple_event(func->name(), param,
                                               new id_name(func->provider()->name()));
                        if (func->provider() == this) {
                            tasks()->push(evt);
                        } else if (func->return_type() != T_NONE) {
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
    
    void terminal::_update_functions() {
        plugin_manager* pm = plugin_manager::instance();
        
        map<string, list<ptr<pf::function>>>::iterator i;
        m_functions.clear();
        
        list<ptr<plugin>> plugins = pm->get_all_plugin();
        for (ptr<plugin> pl : plugins) {
            for (ptr<pf::function> func : pl->supported_functions()) {
                i = m_functions.find(func->name());
                if (i != m_functions.end()) {
                    i->second.push_back(func);
                } else {
                    list<ptr<pf::function>> functions;
                    functions.push_back(func);
                    m_functions[func->name()] = functions;
                }
            }
        }
    }
}
