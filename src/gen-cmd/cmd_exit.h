// GENERATED FROM cmd_exit.h.in.  DO NOT EDIT.

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

#ifndef _FS_SHELL__CMD_EXIT_
#define _FS_SHELL__CMD_EXIT_

// Optional command exit

#ifdef USE_CMD_EXIT



// Exec takes a single argument and parses it into arguments using the
// input_loader.

#include "args.h"
#include "output.h"
#include "globals.h"



/* from cmd_exit.h.in:35 */
extern const char cmd_name_exit[];
#define ENUM_LIST__EXIT \
            /* from cmd_exit.h.in:35 */ \
            COMMAND_INDEX__EXIT,
#define VIRTUAL_ENUM_LIST__EXIT
#define GLOBAL_VARDEF__EXIT \
            /* from cmd_exit.h.in:35 */ \
            const char cmd_name_exit[] = "exit";
#define INITIALIZE__EXIT \
            /* from cmd_exit.h.in:35 */ \
            command_list_names[COMMAND_INDEX__EXIT] = cmd_name_exit;
#define STARTUP_CASE__EXIT
#define RUN_CASE__EXIT \
    case COMMAND_INDEX__EXIT: \
        /* from cmd_exit.h.in:35 */ \
            /* from cmd_exit.h.in:38 */ \
        /* An argument is required.*/ \
        global_err = helper_arg_to_uint(global_arg, 10, 0xff); \
        if (global_arg1_i < 0) { \
            LOG("::  - Bad exit code, or out of range\n"); \
            global_cmd = COMMAND_INDEX__ERR; \
            global_err = 1; \
        } \
        /* Return; do not allow more commands to run.*/ \
        return global_err; \
        break;
#define REQUIRES_ADDL_ARG__EXIT \
            case COMMAND_INDEX__EXIT:

#else /* USE_CMD_EXIT */

#define ENUM_LIST__EXIT
#define VIRTUAL_ENUM_LIST__EXIT
#define GLOBAL_VARDEF__EXIT
#define INITIALIZE__EXIT
#define STARTUP_CASE__EXIT
#define RUN_CASE__EXIT
#define REQUIRES_ADDL_ARG__EXIT
#endif /* USE_CMD_EXIT */

#endif /* _FS_SHELL__CMD_EXIT_ */
