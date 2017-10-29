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
static const string M_START_FRAMEWORK               = "start_framework";
static const string M_STOP_FRAMEWORK                = "stop_framework";

static const string M_LOAD_PLUGIN                   = "load_plugin";
static const string M_UNLOAD_PLUGIN                 = "unload_plugin";

static const string M_UPGRADE_PLUGIN                = "upgrade_plugin";

static const string M_PAUSE_PLUGIN                  = "pause_plugin";
static const string M_RESUME_PLUGIN                 = "resume_plugin";

static const string M_PLUGIN_LOADING                = "plugin_loading";
static const string M_PLUGIN_LOADED                 = "plugin_loaded";
static const string M_PLUGIN_INSTALLING             = "plugin_installing";
static const string M_PLUGIN_INSTALLED              = "plugin_installed";
static const string M_PLUGIN_RUNNING                = "plugin_running";
static const string M_PLUGIN_UPGRADING              = "plugin_upgrading";
static const string M_PLUGIN_UPGRADED               = "plugin_upgrade";
static const string M_PLUGIN_UNINSTALLING           = "plugin_uninstalling";
static const string M_PLUGIN_UNINSTALLED            = "plugin_uninstalled";
static const string M_PLUGIN_UNLOADING              = "plugin_unloading";
static const string M_PLUGIN_UNLOADED               = "plugin_unloaded";

// provided by bus
static const string M_ROUTE                         = "route_event";
static const string M_RESPONSE                      = "response";

// provided by config cneter
static const string M_GET_CONFIG                    = "get_config";
static const string M_PUT_CONFIG                    = "put_config";

// provided by id service
static const string M_SET_GUID                      = "set_guid";
static const string M_FETCH_ADD_GUID                = "fetch_add_guid";
static const string M_FETCH_ADD_GUID_BENCH          = "fetch_add_guidb";
static const string M_GET_CUR_GUID                  = "get_cur_guid";

// provided by barren executor
static const string M_NEW_BARREN_FUNCTION           = "new_bfunc";
static const string M_NEW_COMPOUND_FUNCTION         = "new_cfunc";
static const string M_EXECUTE_BARREN                = "exe_barren";

// provided by barren cache
static const string M_SAVE_CACHE_BARREN             = "save_cbarren";
static const string M_LOAD_CACHE_BARREN             = "load_cbarren";

// provided by barren memory
static const string M_SAVE_BARREN                   = "save_barren";
static const string M_LOAD_BARREN                   = "load_barren";

// provided by ps
static const string M_PUBLISH                       = "publish";

// provided by plugin controller
static const string M_INC_THREAD                    = "inc_thread";
static const string M_DEC_THREAD                    = "dec_thread";
static const string M_SHOW_TASK_COUNT               = "show_ctask";

#endif /* events_h */
