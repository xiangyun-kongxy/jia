//
//  loader.hpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef loader_hpp
#define loader_hpp

#include <plugin/plugin/plugin.hpp>
#include <plugin/plugin/plugin_config.hpp>

#include <list>

using namespace std;

namespace pf {
    
    class plugin_loader {
    public:
        static list<plugin_config*> read_config_file(const string& path,
                                                     char*& buf);
        static ptr<plugin> load_plugin(const plugin_config* conf);
        
    };
    
}

#endif /* loader_hpp */
