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

static const string CFG_PLUGIN                      = "plugin";
static const string CFG_PRIVATE_PARAM               = "parameter";
static const string CFG_LIB_PATH                    = "lib_path";
static const string CFG_PLUGIN_NAME                 = "name";
static const string CFG_INIT_FUNC                   = "init_func";

static const string CFG_CUR_GUID                    = "cur_guid";


// defination of type info
static const string TYPE_INFO                       = "type_info";
static const string OBJECT                          = "object";

static const string OBJ_EVENT                       = "event";
static const string OBJ_SIMPLE_EVENT                = "simple_event";
static const string OBJ_TASK                        = "task";
static const string OBJ_SIMPLE_TASK                 = "simple_task";
static const string OBJ_RESPONSE                    = "response";
static const string OBJ_SIMPLE_RESPONSE             = "simple_response";
static const string OBJ_EXECUTOR                    = "executor";
static const string OBJ_TRIGGER                     = "trigger";
static const string OBJ_PLUGIN                      = "plugin";
static const string OBJ_IDENTIFIER                  = "identifier";
static const string OBJ_THREAD                      = "thread";
static const string OBJ_PLUGIN_THREAD               = "plugin_thread";
static const string OBJ_SERIALIZABLE                = "serializable";
static const string OBJ_CQUEUE                      = "cqueue";


// plugins
static const string PLUGIN_BUS                      = "bus";
static const string PLUGIN_LIFECYCLE                = "lifecycle";
static const string PLUGIN_ID_SERVICE               = "id_service";
static const string PLUGIN_BARREN_CACHE             = "barren_cache";
static const string PLUGIN_MEMORY                   = "memory";
static const string PLUGIN_CONFIG_CENTER            = "config_center";
static const string PLUGIN_BARREN_EXECUTOR          = "barren_executor";

// task processors
static const string EXE_LOAD_CACHE_BARREN           = "load_cache_barren";
static const string EXE_GET_CONFIG                  = "get_config";
static const string EXE_FETCH_ADD_GUID              = "fetch_add_guid";
static const string EXE_GET_CUR_GUID                = "get_cur_guid";
static const string EXE_LOAD_BARREN                 = "load_barren";

// event processors(task without response)
static const string TRIGGER_SAVE_CACHE_BARREN       = "save_cache_barren";
static const string TRIGGER_ON_RESPONSE             = "on_response";
static const string TRIGGER_ON_ROUTE                = "on_route";
static const string TRIGGER_PUT_CONFIG              = "put_config";
static const string TRIGGER_EXECUTE_BARREN          = "execute_barren";
static const string TRIGGER_NEW_BARREN_FUNCTION     = "new_barren_function";
static const string TRIGGER_NEW_COMPOUND_FUNCTION   = "new_compound_function";
static const string TRIGGER_SET_GUID                = "set_guid";
static const string TRIGGER_SAVE_BARREN             = "save_barren";
static const string TRIGGER_START_FRAMEWORK         = "start_framework";

// identifiers
static const string ID_ANY                          = "id_any";
static const string ID_NAME                         = "id_name";
static const string ID_TASK_RESPONSE                = "id_task_response";
static const string ID_SIMPLE_EVENT                 = "id_simple_event";

#endif //NAMES_H
