//
//  exe_load_plugin.h
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef exe_load_plugin_h
#define exe_load_plugin_h

#include <identifier/id_name.h>
#include <response/simple_response.h>
#include <executor/executor.h>
#include <plugin/config.hpp>
#include <manager/plugin_manager.hpp>
#include <errors.h>
#include <names.h>

#include "../load/loader.hpp"

namespace pf {
    
    class load_plugin : public executor {
    public:
        
        virtual ptr<response> run(ptr<plugin> owner, ptr<task> msg) override {
            ptr<lifecycle> lifecycle = owner;
            ptr<serializable> data = msg->param();
            string path;
            data >> path;
            
            // TODO: use load steps
            char* buf;
            list<config*> confs = loader::read_config_file(path, buf);
            list<config*>::const_iterator i;
            for(i = confs.begin(); i != confs.end(); ++i) {
                lifecycle->update_object(new id_name((*i)->get_name()), PS_LOADING);
                ptr<plugin> instance = loader::load_plugin(*i);
                lifecycle->update_object(instance, PS_LOADED);

                list<ptr<object>> plugins;
                do {
                    plugins = lifecycle->get_object(OBJ_PLUGIN, PS_INSTALLING);
                    list<ptr<object>>::iterator j;
                    for (j = plugins.begin(); j != plugins.end(); ++j) {
                        plugin_manager::instance()->add_plugin(*j);
                        lifecycle->update_object(*j, PS_RUNNING);
                    }
                } while (!plugins.empty());
            }
            
            for (i = confs.begin(); i != confs.end(); ++i) {
                delete *i;
            }
            confs.clear();
            delete[] buf;
            
            // TODO: return load result;
            return new simple_response(EC_OK, EM_OK);
        }
        
        virtual string type() const override {
            return EXE_LOAD_PLUGIN;
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == EXE_LOAD_PLUGIN || object::is_kind_of(type_name);
        }
    };
    
}

#endif /* exe_load_plugin_h */
