//
//  dependence_manager.hpp
//  plugin
//
//  Created by xiangyun.kong on 10/18/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef dependence_manager_hpp
#define dependence_manager_hpp

#include <stdio.h>

#include <lib/identifier/identifier.h>
#include <lib/object/object.h>
#include <lib/object/ptr.h>

#include <list>

using namespace kxy;
using namespace std;

namespace pf {

    class dependence_manager {
    private:
        friend void __init_dependence_manager();
        typedef list<pair<ptr<object>,ptr<object>>> container;
        dependence_manager();

    public:
        static dependence_manager* instance();
        
    public:
        void add_depend(ptr<object> obj, ptr<object> be_depend);
        void rm_depend(ptr<object> obj, ptr<object> be_depend);

        bool is_depend_ready(ptr<object> obj);
        bool is_depended(ptr<object> obj);
        
    private:
        container::iterator _exist(ptr<object>, ptr<object>);
        bool _match(ptr<object>, ptr<object>);

    private:
        container m_depend;
        container m_be_depend;

        pthread_mutex_t m_mutex;
    };
    
}
#endif /* dependence_manager_hpp */
