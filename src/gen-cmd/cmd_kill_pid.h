// GENERATED FROM cmd_kill_pid.h.in.  DO NOT EDIT.

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

#ifndef _FS_SHELL__CMD_KILL_PID_
#define _FS_SHELL__CMD_KILL_PID_

// Optional command kill-pid

#ifdef USE_CMD_KILL_PID


#include <signal.h>

#include "output.h"
#include "globals.h"
#include "helpers.h"


/* from cmd_kill_pid.h.in:30 */
extern const char cmd_name_kill_pid_signal[];
#define ENUM_LIST__KILL_PID \
            /* from cmd_kill_pid.h.in:30 */ \
            COMMAND_INDEX__KILL_PID_SIGNAL,
#define VIRTUAL_ENUM_LIST__KILL_PID \
            /* from cmd_kill_pid.h.in:43 */ \
            COMMAND_INDEX__KILL_PID,
#define GLOBAL_VARDEF__KILL_PID \
            /* from cmd_kill_pid.h.in:30 */ \
            const char cmd_name_kill_pid_signal[] = "kill-pid";
#define INITIALIZE__KILL_PID \
            /* from cmd_kill_pid.h.in:30 */ \
            command_list_names[COMMAND_INDEX__KILL_PID_SIGNAL] = cmd_name_kill_pid_signal;
#define STARTUP_CASE__KILL_PID
#define RUN_CASE__KILL_PID \
    case COMMAND_INDEX__KILL_PID_SIGNAL: \
        /* from cmd_kill_pid.h.in:30 */ \
            /* from cmd_kill_pid.h.in:31 */ \
        LOG(":: killing with signal "); \
        LOGLN(global_arg); \
        global_cmd = COMMAND_INDEX__KILL_PID; \
        global_arg1_i = helper_arg_to_uint(global_arg, 10, 0xffff); \
        if (global_arg1_i < 0) { \
            global_err = 1; \
            /* Do not allow the command to kill.*/ \
            global_cmd = COMMAND_INDEX__ERR; \
        } \
        break; \
    case COMMAND_INDEX__KILL_PID: \
        /* from cmd_kill_pid.h.in:43 */ \
            /* from cmd_kill_pid.h.in:44 */ \
        LOG(":: killing PID "); \
        LOGLN(global_arg); \
        global_arg2_i = helper_arg_to_uint(global_arg, 10, 0x7fffffff); \
        if (global_arg2_i < 0) { \
            global_err = 1; \
            /* Allow more kills to happen*/ \
        } else { \
            /* This returns 0 on OK, and -1 on error.*/ \
            /* The command runner just checks, for each arg pass,*/ \
            /* if the global_err is non-zero.*/ \
            global_err = kill(global_arg2_i, global_arg1_i); \
/*printf("[kill debug] kill pid %d with signal %d returned %d\n", global_arg2_i, global_arg1_i, global_err);*/ \
        } \
        break;
#define REQUIRES_ADDL_ARG__KILL_PID

#else /* USE_CMD_KILL_PID */

#define ENUM_LIST__KILL_PID
#define VIRTUAL_ENUM_LIST__KILL_PID
#define GLOBAL_VARDEF__KILL_PID
#define INITIALIZE__KILL_PID
#define STARTUP_CASE__KILL_PID
#define RUN_CASE__KILL_PID
#define REQUIRES_ADDL_ARG__KILL_PID
#endif /* USE_CMD_KILL_PID */

#endif /* _FS_SHELL__CMD_KILL_PID_ */
