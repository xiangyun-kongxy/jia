//
//  simple_task.hpp
//  plugin
//
//  Created by 孔祥云 on 12/24/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef simple_task_hpp
#define simple_task_hpp

#include "task.h"

namespace pf {
    
    class simple_task : public task {
    public:
        DECLARE_TYPE(task, OBJ_SIMPLE_TASK);
        
    private:
        simple_task(const string& task_name, ptr<plugin> caller);
        
    public:
        simple_task(const string& task_name);
        simple_task(const string& task_name, ptr<serializable> param);
        simple_task(const string& task_name, ptr<identifier> proc);
        simple_task(const string& task_name, ptr<serializable> param,
                    ptr<identifier> proc);
        
    public:
        virtual ptr<plugin> caller() const override;
        virtual ptr<identifier> processor() const override;
        virtual ptr<serializable> param() const override;
        string task_name() const;

    public:
        string name() const override {
            return m_task_name;
        }
        
    private:
        ptr<plugin> m_caller;
        ptr<identifier> m_processor;
        string m_task_name;
        ptr<serializable> m_param;
    };

}

#endif /* simple_task_hpp */
