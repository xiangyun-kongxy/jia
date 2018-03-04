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

#include <spl/bsp/lexical/types/bsp_barren.hpp>

#include <spl/general/lfile.hpp>
#include <spl/general/ldir.hpp>

using namespace std;
using namespace mind;

namespace spl {
namespace bsp {
    
    class compiler {
    public:
        compiler();
        
    public:
        void add_dir(const string& path);
        void add_file(const string& file);
        
    public:
        void compile();
        void link();
        
    public:
        void show_barren();
        
    private:
        void compile(ptr<lfile> file);
        
    private:
        ptr<ldir> m_root;
        map<string, ptr<lfile>> m_files;
        list<ptr<bsp_barren>> m_barrens;
    };
    
}
}

#endif /* complier_hpp */
