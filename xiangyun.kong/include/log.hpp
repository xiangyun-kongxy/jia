//
//  log.hpp
//  
//
//  Created by 孔祥云 on 10/21/17.
//
//

#ifndef log_h
#define log_h

#include <common/log/logger.hpp>
#include <lib/object/ptr.h>

namespace kxy {
    
    class logs {
    public:
        static ptr<logger> get_logger(const string& name);
        static void set_logger(const string& name, const string& file, log_level level);
    };
}

#endif /* log_h */
