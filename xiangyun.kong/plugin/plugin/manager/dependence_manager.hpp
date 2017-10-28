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

#include <lib/identifier/identifier.hpp>
#include <lib/object/object.hpp>
#include <lib/object/ptr.hpp>

#include <list>
#include <mutex>

using namespace kxy;
using namespace std;

namespace pf {

    class dependence_manager {
    private:
        friend class plugin_manager;
        friend void __init_dependence_manager();
        friend void __uninit_dependence_manager();
        typedef list<pair<ptr<object>,ptr<object>>> container;
        dependence_manager();
        ~dependence_manager();

    public:
        static dependence_manager* instance();
        
        bool is_depend_ready(ptr<object> obj);
        bool is_depended(ptr<object> obj);

    private:
        void add_depend(ptr<object> obj, ptr<object> be_depend);
        void rm_depend(ptr<object> obj, ptr<object> be_depend);

    private:
        container::iterator _exist(ptr<object>, ptr<object>);
        bool _match(ptr<object>, ptr<object>);
        list<ptr<object>> _extern_sub_obj(ptr<object> obj);

    private:
        container m_depend;
    };
    
}
#endif /* dependence_manager_hpp */
