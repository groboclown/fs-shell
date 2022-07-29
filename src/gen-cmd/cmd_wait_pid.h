// GENERATED FROM cmd_wait_pid.h.in.  DO NOT EDIT.

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

#ifndef _FS_SHELL__CMD_WAIT_PID_
#define _FS_SHELL__CMD_WAIT_PID_

// Optional command wait-pid

#ifdef USE_CMD_WAIT_PID


#include <sys/types.h>
#include <sys/wait.h>

#include "output.h"
#include "globals.h"
#include "helpers.h"


/* from cmd_wait_pid.h.in:31 */
extern const char cmd_name_wait_pid[];
#define ENUM_LIST__WAIT_PID \
            /* from cmd_wait_pid.h.in:31 */ \
            COMMAND_INDEX__WAIT_PID,
#define VIRTUAL_ENUM_LIST__WAIT_PID
#define GLOBAL_VARDEF__WAIT_PID \
            /* from cmd_wait_pid.h.in:31 */ \
            const char cmd_name_wait_pid[] = "wait-pid";
#define INITIALIZE__WAIT_PID \
            /* from cmd_wait_pid.h.in:31 */ \
            command_list_names[COMMAND_INDEX__WAIT_PID] = cmd_name_wait_pid;
#define STARTUP_CASE__WAIT_PID \
    case COMMAND_INDEX__WAIT_PID: \
        /* from cmd_wait_pid.h.in:31 */ \
            /* from cmd_wait_pid.h.in:32 */ \
        global_arg3_i = 0; \
        break;
#define RUN_CASE__WAIT_PID \
    case COMMAND_INDEX__WAIT_PID: \
        /* from cmd_wait_pid.h.in:31 */ \
            /* from cmd_wait_pid.h.in:36 */ \
        /* global_arg1_i == wait pid*/ \
        /* global_arg3_i == last wait pid status.*/ \
        if (global_arg[0] == '*') { \
            /* Should check for global_arg2_i state, and initialize it to -1,*/ \
            /* but that's extra code to check for invalid usage.*/ \
            global_itoa_ptr = shared_itoa(WEXITSTATUS(global_arg3_i), global_itoa); \
            LOG(":: assigning completed exit code "); \
            LOG(global_itoa_ptr); \
            LOG(" to env "); \
            LOGLN(&global_arg[1]); \
            setenv(&global_arg[1], global_itoa_ptr, 1); \
            break; \
        } \
        if (global_arg[0] == '>') { \
            /* Any PID.  The PID that ends will be stored in*/ \
            /* the env at &global_arg[1]*/ \
            global_arg1_i = -1; \
        } else { \
            LOG("::  - using pid "); \
            LOGLN(global_arg); \
            global_arg1_i = helper_arg_to_uint(global_arg, 10, 0x7ffffff); \
            if (global_arg1_i < 0) { \
                LOG("::  - Bad number, or out of range\n"); \
                global_cmd = COMMAND_INDEX__ERR; \
                global_err = 1; \
            } \
        } \
        global_arg2_i = waitpid(global_arg1_i, &global_arg3_i, 0); \
        if (global_arg2_i == -1) { \
            global_err = 1; \
        } else if (global_arg[0] == '>') { \
            global_itoa_ptr = shared_itoa(global_arg2_i, global_itoa); \
            LOG(":: assigning completed PID "); \
            LOG(global_itoa_ptr); \
            LOG(" to env "); \
            LOGLN(&global_arg[1]); \
            setenv(&global_arg[1], global_itoa_ptr, 1); \
        } \
        break;
#define REQUIRES_ADDL_ARG__WAIT_PID

#else /* USE_CMD_WAIT_PID */

#define ENUM_LIST__WAIT_PID
#define VIRTUAL_ENUM_LIST__WAIT_PID
#define GLOBAL_VARDEF__WAIT_PID
#define INITIALIZE__WAIT_PID
#define STARTUP_CASE__WAIT_PID
#define RUN_CASE__WAIT_PID
#define REQUIRES_ADDL_ARG__WAIT_PID
#endif /* USE_CMD_WAIT_PID */

#endif /* _FS_SHELL__CMD_WAIT_PID_ */
