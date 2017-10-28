//
//  file.h
//  plugin
//
//  Created by 孔祥云 on 11/2/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef file_util_h
#define file_util_h

#include <string>

using namespace std;

namespace kxy {
    
    class file_util {
    public:
        static string read(const string& path) {
            FILE* pf = fopen(path.c_str(), "r");
            if (pf != nullptr) {
                fseek(pf, 0, SEEK_END);
                long size = ftell(pf);
                fseek(pf, 0, SEEK_SET);

                char* buf = new char[size + 1];
                string result;

                while(fgets(buf, (int)size, pf) != nullptr) {
                    result += buf;
                }
                fclose(pf);
                delete[] buf;
                
                return result;
            }
            return "";
        }
    };
}

#endif /* file_tuil_h */
