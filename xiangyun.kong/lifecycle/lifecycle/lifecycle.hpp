//
//  lifecycle.hpp
//  lifecycle
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef lifecycle_hpp
#define lifecycle_hpp

#include <plugin/plugin/plugin.h>
#include <plugin/plugin/config.hpp>

namespace pf {

    enum plugin_status {
        PS_UNKNOWN,
        PS_LOADING,
        PS_LOADED,
        PS_INSTALLING,
        PS_INSTALLED,
        PS_WAITINg,
        PS_RUNNING,
        PS_UPGRADING,
        PS_UPGRADED,
        PS_UNINSTALLING,
        PS_UNINSTALLED,
        PS_UNLOADING,
        PS_UNLOADED,
    };
    
    class lifecycle : public plugin {
    public:
        lifecycle();
        virtual ~lifecycle();

    public:
        void set_config(char* buf, const list<config*>& configs);

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

    private:
        map<char*, list<config*>> m_configs;
    };
    
}

#endif /* lifecycle_hpp */
