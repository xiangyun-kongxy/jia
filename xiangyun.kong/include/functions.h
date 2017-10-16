//
//  functions.h
//  
//
//  Created by 孔祥云 on 10/14/17.
//
//

#ifndef functions_h
#define functions_h

// provided by lifecycle
static const string F_START_FRAMEWORK               = "start_framework";
static const string F_STOP_FRAMEWORK                = "stop_framework";

static const string F_LOAD_PLUGIN                   = "load_plugin";
static const string F_UNLOAD_PLUGIN                 = "unload_plugin";

static const string F_UPGRADE_PLUGIN                = "upgrade_plugin";

static const string F_PAUSE_PLUGIN                  = "pause_plugin";
static const string F_RESUME_PLUGIN                 = "resume_plugin";

static const string F_WAIT_TO_RUN                   = "wait_ro_run";

// provided by bus
static const string F_ROUTE                         = "route_event";
static const string F_RESPONSE                      = "response";

// provided by id service
static const string F_FETCH_ADD_GUID                = "fetch_add_guid";
static const string F_GET_CUR_CUID                  = "get_cur_guid";
static const string F_SET_GUID                      = "set_guid";

// provided by config center
static const string F_GET_CONFIG                    = "get_config";
static const string F_PUT_CONFIG                    = "put_config";

// provided by barren executor
static const string F_NEW_BARREN_FUNCTION           = "new_barren_function";
static const string F_NEW_COMPOUND_FUNCTION         = "new_compound_function";
static const string F_EXECUTE_BARREN                = "execute_barren";

// provided by barren cache
static const string F_SAVE_CACHE_BARREN             = "save_cache_barren";
static const string F_LOAD_CACHE_BARREN             = "load_cache_barren";

// provided by barren memory
static const string F_SAVE_BARREN                   = "save_barren";
static const string F_LOAD_BARREN                   = "load_barren";

#endif /* functions_h */
