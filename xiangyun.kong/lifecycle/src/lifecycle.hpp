//
//  lifecycle.hpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef lifecycle_hpp
#define lifecycle_hpp

#include <plugin/plugin.h>

namespace pf {

    enum plugin_status {
        PS_LOADING,
        PS_LOADED,
        PS_INSTALLING,
        PS_RUNNING,
        PS_UPGRADING,
        PS_UPDATING_DEPENDENCE,
        PS_UNLOADING,
        PS_READY,
        PS_UNKNOWN,
    };
    
    class lifecycle : public plugin {
    public:
        lifecycle();

    public:
        void update_object(ptr<object> obj, plugin_status status);
        list<ptr<object>> get_object(const string& type,  plugin_status status);
        
    public:
        virtual string type() const override ;
        virtual bool is_kind_of(const string &type_name) const override ;

    private:
        void remove_identifier(ptr<plugin> plugin);
        bool is_satisfied(ptr<plugin> plugin);
        plugin_status get_object_status(ptr<identifier> id);

    private:
        map<ptr<object>, plugin_status> m_objects;
    };
    
}

#endif /* lifecycle_hpp */
