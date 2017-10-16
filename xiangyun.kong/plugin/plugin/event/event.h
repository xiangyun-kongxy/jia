/**
 * copyright @2016. all rights reserved.
 *
 * @since:  2:19 PM Aug 6, 2016
 * @author: xiangyun kong
 *
 * description:
 *      definition of plugin::event which is the basic message transferred in
 *      the plugin framework
 */

#ifndef PLUGIN_EVENT_H
#define PLUGIN_EVENT_H

#include <lib/object/object.h>
#include <lib/object/ptr.h>
#include <lib/identifier/identifier.h>
#include <lib/serialize/serializable.hpp>

using namespace kxy;
namespace pf {

    class plugin;
    
    /**
     * @since: 2:21 PM Aug 6, 2016
     *
     * *plugin::event* is the basic message transferred in the framework. every
     * interaction between plugin should exchange message by *plugin::event* or
     * *plugin::task*. the different between event and task is multi-cast or single-
     * cast. event is sent to all plugin that matches destination
     */
    class event : public object {
    public:
        /**
         * @return who published the event
         */
        virtual ptr<plugin> deliver() const = 0;
        /**
         * @return the destination of the event
         */
        virtual ptr<identifier> destination() const = 0;
        /**
         * @return parameter of the event if any
         * @see plugin::data
         */
        virtual ptr<serializable> param() const = 0;

        virtual string type() const override {
            return OBJ_EVENT;
        }
        
        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == OBJ_EVENT || object::is_kind_of(type_name);
        }

    };

}

#endif //PLUGIN_EVENT_H
