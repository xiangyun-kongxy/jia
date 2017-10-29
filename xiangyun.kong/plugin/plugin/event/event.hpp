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

#include <lib/object/object.hpp>
#include <lib/object/ptr.hpp>
#include <lib/identifier/identifier.hpp>
#include <lib/serialize/serializable.hpp>

using namespace kxy;
namespace pf {

    class plugin;
    
    /**
     * @since: 2:21 PM Aug 6, 2016
     *
     * *plugin::event* is the basic message transferred in the framework. every
     * interaction between plugin should exchange message by *plugin::event*.
     */
    class event : public object {
    public:
        DECLARE_TYPE(object, OBJ_EVENT);
        
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
        
    };

}

#endif //PLUGIN_EVENT_H
