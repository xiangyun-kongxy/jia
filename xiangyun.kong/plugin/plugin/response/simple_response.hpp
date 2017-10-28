//
// Created by xiangyun.kong on 8/8/16.
//

#ifndef PLUGIN_SIMPLE_RESPONSE_H
#define PLUGIN_SIMPLE_RESPONSE_H

#include <plugin/response/response.hpp>

namespace pf {

    class simple_response : public response {
    public:
        DECLARE_TYPE(response, OBJ_SIMPLE_RESPONSE);
        
    public:
        simple_response(ptr<event> evt, long code, const string& msg,
                        ptr<serializable> context = nullptr);

    public:
        virtual long code() override ;
        virtual string message() override ;
        virtual ptr<serializable> context() override ;

    private:
        long m_code;
        string m_msg;
        ptr<serializable> m_context;
    };

}


#endif //PLUGIN_SIMPLE_RESPONSE_H
