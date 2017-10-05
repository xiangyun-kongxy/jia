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

#include <object/object.h>
#include <object/ptr.h>
#include <identifier/identifier.h>
#include <serialize/serializable.hpp>

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
            return "task";
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "task" || object::is_kind_of(type_name);
        }

    };

}

#endif //PLUGIN_TASK_H
