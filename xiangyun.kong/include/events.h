//
//  events.h
//  
//
//  Created by xiangyun.kong on 10/16/17.
//
//

#ifndef events_h
#define events_h

// provided by lifecycle
static const string EVT_START_FRAMEWORK             = "start_framework";
static const string EVT_STOP_FRAMEWORK              = "stop_framework";

static const string EVT_LOAD_PLUGIN                 = "load_plugin";
static const string EVT_UNLOAD_PLUGIN               = "unload_plugin";

static const string EVT_UPGRADE_PLUGIN              = "upgrade_plugin";

static const string EVT_PAUSE_PLUGIN                = "pause_plugin";
static const string EVT_RESUME_PLUGIN               = "resume_plugin";

static const string EVT_WAIT_TO_RUN                 = "wait_ro_run";

// provided by bus
static const string EVT_ROUTE                       = "route_event";
static const string EVT_RESPONSE                    = "response";

// provided by config cneter
static const string EVT_PUT_CONFIG                  = "put_config";

// provided by id service
static const string EVT_SET_GUID                    = "set_guid";

// provided by barren executor
static const string EVT_NEW_BARREN_FUNCTION         = "new_barren_function";
static const string EVT_NEW_COMPOUND_FUNCTION       = "new_compound_function";
static const string EVT_EXECUTE_BARREN              = "execute_barren";

// provided by barren cache
static const string EVT_SAVE_CACHE_BARREN           = "load_cache_barren";

// provided by barren memory
static const string EVT_SAVE_BARREN                 = "load_barren";

#endif /* events_h */
