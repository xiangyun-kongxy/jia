//
//  plugin_manager.hpp
//  plugin
//
//  Created by xiangyun.kong on 10/3/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef plugin_manager_hpp
#define plugin_manager_hpp

#include <stdio.h>

#include <lib/object/object.h>
#include <plugin/plugin/plugin.h>

#include "plugin_thread.hpp"

using namespace kxy;

namespace pf {

    class plugin_manager : public object {
    private:
        plugin_manager(){};

    public:
        static ptr<plugin_manager> instance();

    public:
        void add_plugin(ptr<plugin> p);
        void delete_plugin(ptr<plugin> p);
        list<ptr<plugin>> find_plugin(ptr<identifier> id);
        list<ptr<plugin>> get_all_plugin();

    public:
        void set_plugin_thread_count(ptr<plugin> p, long count);
        long get_plugin_thread_count(ptr<plugin> p);
        list<ptr<plugin_thread>> get_plugin_thread(ptr<plugin> p);
        ptr<plugin> get_plugin_by_thread_id(pthread_t thread_id);

    private:
        typedef map<ptr<plugin>, list<ptr<plugin_thread>>> container_type;
        container_type m_container;

        map<pthread_t, ptr<plugin>> m_thread_index;
    };
}

#endif /* plugin_manager_hpp */
