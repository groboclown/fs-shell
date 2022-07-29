// GENERATED FROM cmd_exec.h.in.  DO NOT EDIT.

/*
MIT License

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
SOFTWARE.
*/

#ifndef _FS_SHELL__CMD_EXEC_
#define _FS_SHELL__CMD_EXEC_

// Optional command exec

#ifdef USE_CMD_EXEC



// Exec takes a single argument and parses it into arguments using the
// input_loader.

#include <stdlib.h>
#include <stdio.h>
#include "args.h"
#include "output.h"
#include "globals.h"


#ifdef DEBUG
#define EXEC_DEBUG_REPORT \
    LOG(":: Running command ["); \
    LOG(shared_split_argv[0]); \
    LOG("] with arguments ["); \
    for (global_arg2_i = 0; shared_split_argv[global_arg2_i] != NULL; global_arg2_i++) { \
        if (global_arg2_i > 0) { \
            LOG("] ["); \
        } \
        LOG(shared_split_argv[global_arg2_i]); \
    } \
    LOG("]\n");
#else
#define EXEC_DEBUG_REPORT
#endif



/* from cmd_exec.h.in:54 */
extern const char cmd_name_exec[];
#define ENUM_LIST__EXEC \
            /* from cmd_exec.h.in:54 */ \
            COMMAND_INDEX__EXEC,
#define VIRTUAL_ENUM_LIST__EXEC
#define GLOBAL_VARDEF__EXEC \
            /* from cmd_exec.h.in:54 */ \
            const char cmd_name_exec[] = "exec";
#define INITIALIZE__EXEC \
            /* from cmd_exec.h.in:54 */ \
            command_list_names[COMMAND_INDEX__EXEC] = cmd_name_exec;
#define STARTUP_CASE__EXEC
#define RUN_CASE__EXEC \
    case COMMAND_INDEX__EXEC: \
        /* from cmd_exec.h.in:54 */ \
            /* from cmd_exec.h.in:56 */ \
        /* Split the arguments.*/ \
        SHARED_SPLIT__PARSE_ARG \
        EXEC_DEBUG_REPORT \
        /* This launches a new executable and terminates this one immediately.*/ \
        execvp(shared_split_argv[0], (char * const*) shared_split_argv); \
        /* If the code is still running at this point, then there was an error.*/ \
        /* Rather than returning, allow the next command argument to run.*/ \
        /* Additionally, this will allow normal error reporting to report the problem.*/ \
        global_err = 1; \
        break; \
        break;
#define REQUIRES_ADDL_ARG__EXEC

#else /* USE_CMD_EXEC */

#define ENUM_LIST__EXEC
#define VIRTUAL_ENUM_LIST__EXEC
#define GLOBAL_VARDEF__EXEC
#define INITIALIZE__EXEC
#define STARTUP_CASE__EXEC
#define RUN_CASE__EXEC
#define REQUIRES_ADDL_ARG__EXEC
#endif /* USE_CMD_EXEC */

#endif /* _FS_SHELL__CMD_EXEC_ */
