/**
 * copyright @2016. all rights reserved.
 *
 * @since:  5:32 PM Aug 6, 2016
 * @author: xiangyun kong
 *
 * description:
 *     ☄ names constant definitions
 */

#ifndef NAMES_H
#define NAMES_H

#include <string>

using namespace std;

// defination of type info
static const string TYPE_INFO                       = "type_info";
static const string OBJECT                          = "object";

static const string OBJ_EVENT                       = "event";
static const string OBJ_SIMPLE_EVENT                = "sevent";
static const string OBJ_RESPONSE                    = "response";
static const string OBJ_SIMPLE_RESPONSE             = "sresponse";
static const string OBJ_EXECUTOR                    = "executor";
static const string OBJ_PLUGIN                      = "plugin";
static const string OBJ_IDENTIFIER                  = "identifier";
static const string OBJ_THREAD                      = "thread";
static const string OBJ_PLUGIN_THREAD               = "pthread";
static const string OBJ_HELP_THREAD                 = "gthread";
static const string OBJ_SERIALIZABLE                = "serializable";
static const string OBJ_CQUEUE                      = "cqueue";
static const string OBJ_LOGGER                      = "logger";
static const string OBJ_SCHEDULER                   = "scheduler";
static const string OBJ_SWITCHER                    = "switcher";
static const string OBJ_DELIVER                     = "deliver";
static const string OBJ_DELIVER_MANAGER             = "dlvmanager";

static const string DLV_RESPONSE                    = "dlvresponse";

// plugins
static const string PLUGIN_BUS                      = "bus";
static const string PLUGIN_LIFECYCLE                = "lifecycle";
static const string PLUGIN_ID_SERVICE               = "sid";
static const string PLUGIN_BARREN_CACHE             = "cbarren";
static const string PLUGIN_MEMORY                   = "memory";
static const string PLUGIN_CONFIG_CENTER            = "cfgcenter";
static const string PLUGIN_BARREN_EXECUTOR          = "exebarren";
static const string PLUGIN_PS                       = "pub_sub";
static const string PLUGIN_CONTROLLER               = "plugin_ctrl";

// task processors
static const string EXE_LOAD_CACHE_BARREN           = "load_cbarren";
static const string EXE_GET_CONFIG                  = "get_config";
static const string EXE_FETCH_ADD_GUID              = "fetch_add_guid";
static const string EXE_FETCH_ADD_GUID_BENCH        = "fetch_add_guidb";
static const string EXE_GET_CUR_GUID                = "get_cur_guid";
static const string EXE_LOAD_BARREN                 = "load_barren";
static const string EXE_SAVE_CACHE_BARREN           = "save_cbarren";
static const string EXE_ON_RESPONSE                 = "response";
static const string EXE_ON_ROUTE                    = "route";
static const string EXE_PUT_CONFIG                  = "put_config";
static const string EXE_EXECUTE_BARREN              = "exe_barren";
static const string EXE_NEW_BARREN_FUNCTION         = "new_bfunc";
static const string EXE_NEW_COMPOUND_FUNCTION       = "new_cfunc";
static const string EXE_SET_GUID                    = "set_guid";
static const string EXE_SAVE_BARREN                 = "save_barren";
static const string EXE_START_FRAMEWORK             = "start_framework";
static const string EXE_STOP_FRAMEWORK              = "stop_framework";
static const string EXE_LOAD_PLUGIN                 = "load_plugin";
static const string EXE_UNLOAD_PLUGIN               = "unload_plugin";
static const string EXE_PUBLISHER                   = "publish";
static const string EXE_INC_THREAD                  = "inc_thread";
static const string EXE_DEC_THREAD                  = "dec_thread";
static const string EXE_SHOW_TASK_COUNT             = "show_ctask";


// identifiers
static const string ID_ANY                          = "id_any";
static const string ID_NAME                         = "id_name";
static const string ID_TASK_RESPONSE                = "id_response";
static const string ID_SIMPLE_EVENT                 = "id_sevent";

#endif //NAMES_H
