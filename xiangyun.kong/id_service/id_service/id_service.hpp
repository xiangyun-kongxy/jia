/*
 *  id_service.hpp
 *  id_service
 *
 *  Created by 孔祥云 on 10/14/17.
 *  Copyright © 2017 孔祥云. All rights reserved.
 *
 */

#ifndef id_service_
#define id_service_

#include <plugin/plugin.h>

/* The classes below are exported */
#pragma GCC visibility push(default)

using namespace pf;

namespace kxy {
    
    class id_service : public plugin
    {
    public:
        id_service();
        virtual ~id_service();
        
    public:
        void set_guid(long id);
        long get_guid();
        long fetch_add_guid();
        
    public:
        virtual string type() const override ;
        virtual bool is_kind_of(const string &type_name) const override ;
        
    private:
        void load_guid();
        void save_guid();
        
    private:
        atomic_long m_cur_id;
    };

}

#pragma GCC visibility pop
#endif
