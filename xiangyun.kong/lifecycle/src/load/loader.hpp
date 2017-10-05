//
//  loader.hpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef loader_hpp
#define loader_hpp

#include <plugin/plugin.h>
#include <plugin/config.hpp>
#include <list>

using namespace std;

namespace pf {
    
    class loader {
    public:
        static list<config*> read_config_file(const string& path);
        static ptr<plugin> load_plugin(const config* conf);
        
    };
    
}

#endif /* loader_hpp */
