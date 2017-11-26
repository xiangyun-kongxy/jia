//
//  complier.cpp
//  spl
//
//  Created by 孔祥云 on 11/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#include "bsp_complier.hpp"

#include <lib/fs/file_util.hpp>

#include <dirent.h>
#include <iostream>

using namespace std;

namespace spl {
namespace bsp {
    
    map<long, ptr<barren>> complier::complie_path(const string& path) {
        return complie_files(file_util::file_in_dir(path.c_str(), ".bsp"));
    }
    
    map<long, ptr<barren>> complier::complie_file(const string& file) {
        char* buf = file_util::read_to_buf(file);
        
        map<long, ptr<barren>> result = complie_buf(buf);
        
        delete[] buf;
        return result;
    }
    
    map<long, ptr<barren>> complier::complie_files(const list<string>& files) {
        map<long, ptr<barren>> result;
        
        for (string file : files) {
            map<long, ptr<barren>> t = complie_file(file);
            for (pair<long, ptr<barren>> value : t) {
                if (result.find(value.first) != result.end()) {
                    // TODO: error
                } else {
                    result[value.first] = value.second;
                }
            }
        }
        
        return result;
    }
    
    map<long, ptr<barren>> complier::complie_buf(char* buf) {
        map<long, ptr<barren>> result;
        return result;
    }
    
}
}
