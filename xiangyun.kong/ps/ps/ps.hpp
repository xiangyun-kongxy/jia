/*
 *  ps.hpp
 *  ps
 *
 *  Created by xiangyun.kong on 10/28/17.
 *  Copyright © 2017 xiangyun.kong. All rights reserved.
 *
 */

#ifndef ps_
#define ps_

#include <plugin/plugin/plugin.hpp>

#include <ipc.hpp>

#include <ps/slot/slot.hpp>
#include <ps/index/ps_index_selector.hpp>


namespace pf {

    class ps : public plugin {
    public:
        DECLARE_TYPE(plugin, PLUGIN_PS);
        
        IMPL_BEGIN
        IMPL_END

    public:
        ps();

    public:
        virtual ptr<response> do_task(ptr<event> evt) override;

    public:
        long subscribe(ptr<object> what);
        ptr<object> wait(long pos);
        
        void subscribe(ptr<object> what, fcallback callback);

        void publish(ptr<object> obj);

    private:
        slot m_slot;
        ps_index_selector m_indexes;

        ptr<executor> m_publisher;
    };

}

#endif
