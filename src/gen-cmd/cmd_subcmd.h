// GENERATED FROM cmd_subcmd.h.in.  DO NOT EDIT.

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

#ifndef _FS_SHELL__CMD_SUBCMD_
#define _FS_SHELL__CMD_SUBCMD_

// Optional command subcmd

#ifdef USE_CMD_SUBCMD



#include <stdlib.h>
#include "args.h"
#include "output.h"
#include "globals.h"
#include "command_runner.h"


/* from cmd_subcmd.h.in:33 */
extern const char cmd_name_subcmd[];
#define ENUM_LIST__SUBCMD \
            /* from cmd_subcmd.h.in:33 */ \
            COMMAND_INDEX__SUBCMD,
#define VIRTUAL_ENUM_LIST__SUBCMD
#define GLOBAL_VARDEF__SUBCMD \
            /* from cmd_subcmd.h.in:33 */ \
            const char cmd_name_subcmd[] = "subcmd";
#define INITIALIZE__SUBCMD \
            /* from cmd_subcmd.h.in:33 */ \
            command_list_names[COMMAND_INDEX__SUBCMD] = cmd_name_subcmd;
#define STARTUP_CASE__SUBCMD
#define RUN_CASE__SUBCMD \
    case COMMAND_INDEX__SUBCMD: \
        /* from cmd_subcmd.h.in:33 */ \
            /* from cmd_subcmd.h.in:35 */ \
        /* Split the arguments.*/ \
        shared_split_input_argv[2] = global_arg; \
        shared_split_arg_state = args_setup_tokenizer( \
            3, (char **) shared_split_input_argv, \
            /* Any way to force this to not parse env?*/ \
            1); \
        global_err = command_runner(shared_split_arg_state); \
        break;
#define REQUIRES_ADDL_ARG__SUBCMD

#else /* USE_CMD_SUBCMD */

#define ENUM_LIST__SUBCMD
#define VIRTUAL_ENUM_LIST__SUBCMD
#define GLOBAL_VARDEF__SUBCMD
#define INITIALIZE__SUBCMD
#define STARTUP_CASE__SUBCMD
#define RUN_CASE__SUBCMD
#define REQUIRES_ADDL_ARG__SUBCMD
#endif /* USE_CMD_SUBCMD */

#endif /* _FS_SHELL__CMD_SUBCMD_ */
