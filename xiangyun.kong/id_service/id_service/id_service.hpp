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

#include <lib/identifier/id_name.hpp>

#include <plugin/plugin/plugin.hpp>

#include <messages.hpp>

/* The classes below are exported */
#pragma GCC visibility push(default)

using namespace pf;

namespace kxy {
    
    class id_service : public plugin
    {
    public:
        DECLARE_TYPE(plugin, PLUGIN_ID_SERVICE);
        
        IMPL_BEGIN
        IMPL_F(T_INT, M_FETCH_ADD_GUID)
        IMPL_F(T_INT, M_FETCH_ADD_GUID_BENCH, T_INT)
        IMPL_F(T_INT, M_GET_CUR_GUID)
        IMPL_F(T_NONE, M_SET_GUID, T_INT)
        IMPL_END
    public:
        id_service();
        
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
            
            dependence.push_back(new id_name(M_GET_CONFIG));
            dependence.push_back(new id_name(M_PUT_CONFIG));
            return dependence;
        }

        virtual void resume() override;
        virtual void uninit() override;

    private:
        atomic_long m_cur_id;
    };

}

#pragma GCC visibility pop
#endif
