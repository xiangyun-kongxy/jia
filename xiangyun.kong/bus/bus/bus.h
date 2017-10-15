//
// Created by 孔祥云 on 8/10/16.
//

#ifndef PLUGIN_BUS_H
#define PLUGIN_BUS_H

#include <plugin/plugin.h>
#include <sys/semaphore.h>
#include <pthread.h>
#include <object/ptr.h>
#include <ipc.hpp>

namespace pf {
    
    class bus : public plugin {
    public:
        bus();
        virtual ~bus();
        
    public:
        ptr<response> wait_respond(ptr<task>);
        
        void add_pending_task(ptr<task>,callback);
        void add_response(ptr<task>,ptr<response>);
        
    public:
        virtual string type() const override ;
        virtual bool is_kind_of(const string &type_name) const override ;
        
    private:
        map<ptr<task>,callback> m_pending_task;
        map<ptr<task>,ptr<response>> m_done_task;
        
        sem_t* m_sem;
        pthread_mutex_t m_mutex;
    };
    
}

#endif //PLUGIN_BUS_H
