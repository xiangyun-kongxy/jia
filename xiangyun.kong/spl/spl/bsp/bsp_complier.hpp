//
//  complier.hpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef complier_hpp
#define complier_hpp

#include <string>
#include <list>
#include <map>

#include <barren/barren.hpp>

using namespace std;
using namespace mind;

namespace spl {
namespace bsp {
    
    class complier {
    public:
        static map<long, ptr<barren>> complie_path(const string& path);
        static map<long, ptr<barren>> complie_file(const string& file);
        static map<long, ptr<barren>> complie_files(const list<string>& files);
        static map<long, ptr<barren>> complie_buf(char* buf);
    };
    
}
}

#endif /* complier_hpp */
