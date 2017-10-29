//
//  function.hpp
//  plugin
//
//  Created by 孔祥云 on 10/29/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef function_h
#define function_h

#include <lib/object/object.hpp>

#include <plugin/function/type.hpp>

namespace pf {
    
#define IMPL_BEGIN                                                          \
    virtual list<ptr<pf::function>> supported_functions() const override {  \
        list<ptr<pf::function>> supported;
    
#define IMPL_F(ret, name, ...)                                              \
        supported.push_back(new pf::function((kxy::object*)this, ret, name, \
                            {__VA_ARGS__}));
    
#define IMPL_END                                                            \
        return supported;                                                   \
    }
    
    class function : public object {
    public:
        DECLARE_TYPE(object, OBJ_FUNCTION);
        
    public:
        function(ptr<object> provider, TYPE ret, string name,
                 initializer_list<TYPE> param_type) {
            m_provider = provider;
            m_name = name;
            m_ret_type = ret;
            for (TYPE ty : param_type) {
                m_param_types.push_back(ty);
            }
        }
        
    public:
        virtual string name() const override {
            return m_name;
        }
        
        ptr<object> provider() const {
            return m_provider;
        }
        
        TYPE return_type() const {
            return m_ret_type;
        }
        
        list<TYPE> param_type() const {
            return m_param_types;
        }
        
    private:
        ptr<object> m_provider;
        string m_name;
        TYPE m_ret_type;
        list<TYPE> m_param_types;
    };
}

#endif /* function_h */
