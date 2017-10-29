//
//  ps_index_selector.hpp
//  ps
//
//  Created by xiangyun.kong on 10/28/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef ps_index_selector_h
#define ps_index_selector_h

#include "ind_id.hpp"
#include "ind_name.hpp"
#include "ind_rsp.hpp"
#include "ind_seq.hpp"


namespace pf {

    class ps_index_selector {
    public:
        ps_index* select(ptr<object> obj) {
            if (obj->type() == ID_TASK_RESPONSE) {
                return &m_ind_rsp;
            } else if (obj->type() == ID_NAME) {
                return &m_ind_name;
            } else if (obj->is_kind_of(OBJ_IDENTIFIER)) {
                return &m_ind_seq;
            } else {
                return &m_ind_id;
            }
        }

    public:
        operator list<ps_index*>() {
            list<ps_index*> result = {
                &m_ind_id, &m_ind_name, &m_ind_rsp, &m_ind_seq};
            return result;
        }

    private:
        ind_id m_ind_id;
        ind_name m_ind_name;
        ind_rsp m_ind_rsp;
        ind_seq m_ind_seq;
    };
}

#endif /* ps_index_selector_h */
