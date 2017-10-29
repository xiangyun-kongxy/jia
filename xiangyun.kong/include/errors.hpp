/**
 * copyright @2016. all rights reserved.
 *
 * @since:  17:14 8/23/16
 * @author: xiangyun kong
 *
 * description:
 *      
 */

#ifndef PLUGIN_ERRORS_H
#define PLUGIN_ERRORS_H

#include <string>

using namespace std;

static const long EC_OK = 0L;
static const long EC_WEB_OK = 200L;
static const string EM_OK = "ok";

static const long EC_TASK_NOT_SUPPORTED = 1L;
static const string EM_TASK_NOT_SUPPORTED = "passed task is not supported";

static const long EC_NOT_EXIST = 2L;
static const string EM_NOT_EXIST = "not exist";

static const long EC_PARAM = 3L;
static const string EM_PARAM = "parameter is invalid";

static const long EC_PLUGIN_NOT_FOUND = 4L;
static const string EM_PLUGIN_NOT_FOUND = "plugin not found";

#endif //PLUGIN_ERRORS_H
