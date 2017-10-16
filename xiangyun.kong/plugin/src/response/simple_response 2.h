//
// Created by xiangyun.kong on 8/8/16.
//

#ifndef PLUGIN_SIMPLE_RESPONSE_H
#define PLUGIN_SIMPLE_RESPONSE_H

#include <response/response.h>

namespace plugin {

    class simple_response : public response {
    public:
        simple_response(long code, const string& msg, ptr<data> context = nullptr);

    public:
        virtual long code() override ;
        virtual string message() override ;
        virtual ptr<data> context() override ;

    public:
        virtual string type() const override ;
        virtual bool is_kind_of(const string &type_name) const override ;

    private:
        long m_code;
        string m_msg;
        ptr<data> m_context;
    };

}


#endif //PLUGIN_SIMPLE_RESPONSE_H