/**
 * copyright @2016. all rights reserved.
 *
 * @since:  12:53 8/11/16
 * @author: xiangyun kong
 *
 * description:
 *
 */

#ifndef PLUGIN_THREAD_H
#define PLUGIN_THREAD_H

#include <object/object.h>
#include <semaphore.h>

namespace kxy {
    
    class thread : public object {
    public:
        thread();
        virtual ~thread();
        
    public:
        virtual string type() const override;
        virtual bool is_kind_of(const string &type_name) const override ;
        
    public:
        virtual long start();
        virtual long pause();
        virtual long resume();
        virtual long stop(bool force = false);
        
    public:
        virtual pthread_t thread_id() const;
        
    private:
        static void* thread_func(void *);
        
    public:
        virtual void* run_once() = 0;

    protected:
        pthread_mutex_t m_mutex;
        enum status {
            pending,
            pausing,
            paused,
            resuming,
            running,
            destroying,
            destroyed,
        };
        atomic_long m_status;
        pthread_t m_thread;
    
    protected:
        virtual void update_status();
        virtual void change_status(status s);

        status get_status();
    };

}

#endif //PLUGIN_THREAD_H

