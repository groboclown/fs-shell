// GENERATED FROM cmd_chmod.h.in.  DO NOT EDIT.

/* MIT License

Copyright (c) 2022 groboclown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#ifndef _FS_SHELL__CMD_CHMOD_
#define _FS_SHELL__CMD_CHMOD_

// Optional command chmod

#ifdef USE_CMD_CHMOD


#include <sys/stat.h>
#include <fcntl.h>

#include "output.h"
#include "globals.h"
#include "helpers.h"


/* from cmd_chmod.h.in:31 */
extern const char cmd_name_chmod__mode[];
#define ENUM_LIST__CHMOD \
            /* from cmd_chmod.h.in:31 */ \
            COMMAND_INDEX__CHMOD__MODE,
#define VIRTUAL_ENUM_LIST__CHMOD \
            /* from cmd_chmod.h.in:44 */ \
            COMMAND_INDEX__CHMOD__RUN,
#define GLOBAL_VARDEF__CHMOD \
            /* from cmd_chmod.h.in:31 */ \
            const char cmd_name_chmod__mode[] = "chmod";
#define INITIALIZE__CHMOD \
            /* from cmd_chmod.h.in:31 */ \
            command_list_names[COMMAND_INDEX__CHMOD__MODE] = cmd_name_chmod__mode;
#define STARTUP_CASE__CHMOD
#define RUN_CASE__CHMOD \
    case COMMAND_INDEX__CHMOD__MODE: \
        /* from cmd_chmod.h.in:31 */ \
            /* from cmd_chmod.h.in:32 */ \
        LOG(":: using mode "); \
        LOGLN(global_arg); \
        global_cmd = COMMAND_INDEX__CHMOD__RUN; \
        global_arg1_i = helper_arg_to_uint(global_arg, 8, 07777); \
        if (global_arg1_i < 0) { \
            LOG("::  - Bad base 8 number, or out of range\n"); \
            global_cmd = COMMAND_INDEX__ERR; \
            global_err = 1; \
        } \
        break; \
    case COMMAND_INDEX__CHMOD__RUN: \
        /* from cmd_chmod.h.in:44 */ \
            /* from cmd_chmod.h.in:45 */ \
        LOG(":: chmod on "); \
        LOGLN(global_arg); \
        global_err = chmod(global_arg, global_arg1_i); \
        break;
#define REQUIRES_ADDL_ARG__CHMOD

#else /* USE_CMD_CHMOD */

#define ENUM_LIST__CHMOD
#define VIRTUAL_ENUM_LIST__CHMOD
#define GLOBAL_VARDEF__CHMOD
#define INITIALIZE__CHMOD
#define STARTUP_CASE__CHMOD
#define RUN_CASE__CHMOD
#define REQUIRES_ADDL_ARG__CHMOD
#endif /* USE_CMD_CHMOD */

#endif /* _FS_SHELL__CMD_CHMOD_ */
