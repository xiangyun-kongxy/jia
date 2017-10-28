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

#include <lib/object/object.hpp>

#include <semaphore.h>

namespace kxy {
    
    enum thread_status {
        pending,
        pausing,
        paused,
        resuming,
        running,
        stopping,
        stopped,
    };

    class thread : public object {
    public:
        thread();
        virtual ~thread();
        DECLARE_TYPE(object, OBJ_THREAD);
        
    public:
        virtual long pause();
        virtual long resume();

    public:
        virtual pthread_t thread_id() const;
        thread_status status();

    private:
        static void* thread_func(void *);
        
    protected:
        virtual void update_status();
        virtual void change_status(thread_status s);
        virtual void wait_status();
        virtual void kill_thread();
        
    public:
        virtual void* run_once() = 0;

    protected:
        atomic_long m_status;
        pthread_t m_thread;
        sem_t* m_status_changing;
        sem_t* m_status_changed;
    };

}

#endif //PLUGIN_THREAD_H

