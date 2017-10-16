/**
 * copyright @2016. all rights reserved.
 *
 * @since:  5:10 PM Aug 6, 2016
 * @author: xiangyun kong
 *
 * description:
 *     definition of *plugin::object*, which is the base of all identifiable
 *     classes
 */

#ifndef PLUGIN_OBJECT_H
#define PLUGIN_OBJECT_H

#include <string>
#include <uuid/uuid.h>

#include <lib/object/reference.h>
#include <lib/object/type_info.h>

#include <names.h>

using namespace std;
namespace kxy {
    
    class object : public reference, public type_info {
    public:
        virtual string type() const {
            return OBJECT;
        }

        virtual bool is_kind_of(const string& type_name) const {
            return type_name == OBJECT || type_info::is_kind_of(type_name);
        }

    public:
        virtual string name() const {
            return type();
        }
        
        virtual string id() const {
            return m_id;
        }
        
    public:
        object() {
            unsigned char uuid[sizeof(uuid_t) + 1] = {0};
            uuid_generate(uuid);
            m_id = (char*)uuid;
        }

        virtual ~object() {
            
        }
        
        
    private:
        string m_id;
    };
    
}

#endif //PLUGIN_OBJECT_H
