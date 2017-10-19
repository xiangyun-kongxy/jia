/**
 * copyright @2016. all rights reserved.
 *
 * @since  2:31 PM Aug 6, 2016
 * @author xiangyun kong
 *
 * description:
 *     definition of identifier which is used for identify instances that
 *     inherited from plugin::object
 */

#ifndef PLUGIN_PLUGIN_IDENTIFIER_H
#define PLUGIN_PLUGIN_IDENTIFIER_H

#include <lib/object/object.h>
#include <lib/object/ptr.h>
#include <names.h>

namespace kxy {

    /**
     * @since 2:33 PM Aug 6, 2016
     *
     * identifier is used for identifying instances that inherited from
     * *plugin::object*
     */
    class identifier : public object {
    public:
        DECLARE_TYPE(object, OBJ_IDENTIFIER);
        
    public:
        identifier(ptr<identifier> base) {
            m_base = base;
        }
        
    public:
        /**
         * using whole object for matching
         *
         * @param obj the object to be identified
         * @return whether the identifier identify the object
         */
        virtual bool match(ptr<object> obj) {
            if(m_base != nullptr) {
                return m_base->match(obj);
            }
            return true;
        }
        
    protected:
        ptr<identifier> m_base;
    };
}

#endif //PLUGIN_PLUGIN_IDENTIFIER_H
