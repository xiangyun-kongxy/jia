/**
 * copyright @2016. all rights reserved.
 *
 * @since:  2:19 PM Aug 6, 2016
 * @author: xiangyun kong
 *
 * description:
 *
 */

#ifndef PLUGIN_TASK_H
#define PLUGIN_TASK_H

#include <lib/object/object.h>
#include <lib/object/ptr.h>
#include <lib/identifier/identifier.h>
#include <lib/serialize/serializable.hpp>

using namespace kxy;

namespace pf {

    class plugin;

    /**
     * a task runs one time at most
     */
    class task : public object {
    public:
        DECLARE_TYPE(object, OBJ_TASK);
        
    public:
        /**
         * @return who called the task
         */
        virtual ptr<plugin> caller() const = 0;
        /**
         * @return who is wanted to do the task
         */
        virtual ptr<identifier> processor() const = 0;
        /**
         * @return parameter for processing task
         */
        virtual ptr<serializable> param() const = 0;

    };

}

#endif //PLUGIN_TASK_H
