//
//  ps_index.hpp
//  ps
//
//  Created by xiangyun.kong on 10/28/17.
//  Copyright © 2017 xiangyun.kong. All rights reserved.
//

#ifndef ps_index_h
#define ps_index_h

#include <lib/object/object.hpp>
#include <lib/object/ptr.hpp>

#include <ipc.hpp>

namespace pf {

    class ps_index {
    public:
        virtual list<long> search(ptr<object> obj) = 0;

        virtual void registe(ptr<object> obj, long slot) = 0;
        virtual void registe(ptr<object> obj, fcallback callback) = 0;
    };
}

#endif /* ps_index_h */
