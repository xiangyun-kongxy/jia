//
//  file.h
//  plugin
//
//  Created by 孔祥云 on 11/2/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef file_util_h
#define file_util_h

#include <dirent.h>
#include <sys/stat.h>

#include <string>
#include <list>

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
        
        static char* read_to_buf(const string& path) {
            FILE* pf = fopen(path.c_str(), "r");
            if (pf != nullptr) {
                fseek(pf, 0, SEEK_END);
                long size = ftell(pf);
                fseek(pf, 0, SEEK_SET);
                
                char* buf = new char[size + 1];
                fread(buf, 1, size, pf);
                buf[size] = 0;
                
                fclose(pf);
                return buf;
            }
            return nullptr;
        }
        
        static list<string> file_in_dir(const char* path, const char* pattern) {
            list<string> result;
            
            dirent* filename;
            DIR* dir = opendir(path);
            if (dir != nullptr) {
                while ((filename = readdir(dir)) != nullptr) {
                    if (strcmp(filename->d_name, ".") == 0 ||
                        strcmp(filename->d_name, "..") == 0) {
                        continue;
                    }
                    
                    struct stat s;
                    lstat(filename->d_name, &s);
                    if (S_ISDIR(s.st_mode)) {
                        for (string file : file_in_dir(filename->d_name,
                                                       pattern)) {
                            result.push_back(file);
                        }
                    } else {
                        const char* ptr = filename->d_name;
                        do {
                            ptr = strstr(ptr, pattern);
                            if (ptr != nullptr &&
                                strlen(ptr) == strlen(pattern)) {
                                result.push_back(filename->d_name);
                                break;
                            }
                            ++ptr;
                        } while (ptr != nullptr);
                    }
                }
                closedir(dir);
            }
            
            return result;
        }
    };
}

#endif /* file_tuil_h */
