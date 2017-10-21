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

#include <lib/identifier/id_name.h>

#include <plugin/plugin/plugin.h>

#include <functions.h>
#include <events.h>

/* The classes below are exported */
#pragma GCC visibility push(default)

using namespace pf;

namespace kxy {
    
    class id_service : public plugin
    {
    public:
        id_service();
        DECLARE_TYPE(plugin, PLUGIN_ID_SERVICE);
        
    public:
        void set_guid(long id);
        long get_guid();
        long fetch_add_guid();
        long fetch_add_guid(long size);
        
    private:
        void load_guid();
        void save_guid();

    public:
        virtual list<ptr<identifier>> depend_on() const override {
            list<ptr<identifier>> dependence;
            
            dependence.push_back(new id_name(F_GET_CONFIG));
            dependence.push_back(new id_name(EVT_PUT_CONFIG));
            return dependence;
        }

        virtual void init() override;
        virtual void uninit() override;

    private:
        atomic_long m_cur_id;
    };

}

#pragma GCC visibility pop
#endif
