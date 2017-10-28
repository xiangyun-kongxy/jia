//
//  plugin_status.hpp
//  plugin
//
//  Created by xiangyun.kong on 10/27/17.
//  Copyright © 2017 孔祥云. All rights reserved.
//

#ifndef plugin_status_h
#define plugin_status_h

namespace pf {

    enum plugin_status {
        PS_UNKNOWN,
        PS_LOADING,
        PS_LOADED,
        PS_INSTALLING,
        PS_INSTALLED,
        PS_RUNNING,
        PS_UNINSTALLING,
        PS_UNINSTALLED,
        PS_UNLOADING,
        PS_UNLOADED,
    };

}

#endif /* plugin_status_h */
