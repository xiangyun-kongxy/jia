//
//  lifecycle_function.h
//  lifecycle
//
//  Created by xiangyun.kong on 12/28/16.
//  Copyright © 2016 孔祥云. All rights reserved.
//

#ifndef lifecycle_function_h
#define lifecycle_function_h

#include <string>
using namespace std;

static const string CFG_PLUGIN                      = "plugin";

static const string F_LOAD_PLUGIN                   = "load_plugin";
static const string F_QUERY_PLUGIN                  = "query_plugin";

static const string D_QUERY_PLUGIN_REQUEST          = "query_plugin_request_data";
static const string D_QUERY_PLUGIN_RSP              = "query_plugin_rsp_data";
static const string D_LOAD_PLUGIN_REQUEST           = "load_plugin_request_data";


static const string DF_QUERY_PLUGIN_REQUEST_NAME    = "name";
static const string DF_QUERY_PLUGIN_RSP_PLUGIN      = "plugin";
static const string DF_LOAD_PLUGIN_REQUEST_PATH     = "path";

static const string ANY_PLUGIN                      = "*";

#endif /* lifecycle_function_h */
