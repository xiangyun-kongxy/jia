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

#include <object/object.h>
#include <object/ptr.h>

namespace kxy {

    /**
     * @since 2:33 PM Aug 6, 2016
     *
     * identifier is used for identifying instances that inherited from
     * *plugin::object*
     */
    class identifier : public object {
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
        
        virtual string type() const override {
            return "identifier";
        }

        virtual bool is_kind_of(const string &type_name) const override {
            return type_name == "identifier" || object::is_kind_of(type_name);
        }
        
    protected:
        ptr<identifier> m_base;
    };
}

#endif //PLUGIN_PLUGIN_IDENTIFIER_H
