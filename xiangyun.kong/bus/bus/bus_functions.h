/**
 * copyright @2016. all rights reserved.
 *
 * @since:  10:56 PM 8/10/16
 * @author: xiangyun kong
 *
 * description:
 *
 */

#ifndef PLUGIN_FUNCTIONS_H
#define PLUGIN_FUNCTIONS_H

#include <string>
using namespace std;

static const string F_ROUTE_TASK                        = "route_task";
static const string F_ROUTE_EVENT                       = "route_event";
static const string F_RESPONSE                          = "response";
static const string F_QUERY_CURRENT_THREAD              = "query_current_thread";

static const string D_ROUTE                             = "route_data";
static const string D_QUERY_CURRENT_THREAD_RSP          = "query_current_thread_rsp_data";
static const string D_RESPONSE                          = "response_data";

static const string DF_ROUTE_MESSAGE                    = "message";
static const string DF_QUERY_CURRENT_THREAD_RSP_THREAD  = "thread";
static const string DF_RESPONSE_TASK                    = "task";
static const string DF_RESPONSE_RESPONSE                = "response";

static const long EC_PLUGIN_NOT_EXIST                   = 10000;
static const string EM_PLUGIN_NOT_EXIST                 = "plugin not exist";

#endif //PLUGIN_FUNCTIONS_H
