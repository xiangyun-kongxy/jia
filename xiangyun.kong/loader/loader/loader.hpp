/*
 *  loader.hpp
 *  loader
 *
 *  Created by 孔祥云 on 12/31/16.
 *  Copyright © 2016 孔祥云. All rights reserved.
 *
 */

#ifndef loader_
#define loader_

#include <string>

using namespace std;

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace pf {

    class loader
    {
    public:
        loader(const string& conf_path);
        
    public:
        void load();
        
    private:
        string m_plugin_conf_path;
    };
    
}

#pragma GCC visibility pop
#endif
