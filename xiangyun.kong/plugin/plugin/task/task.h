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

        virtual string type() const override {
            return OBJ_TASK;
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == OBJ_TASK || object::is_kind_of(type_name);
        }

    };

}

#endif //PLUGIN_TASK_H
