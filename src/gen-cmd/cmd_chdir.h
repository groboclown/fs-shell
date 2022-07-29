// GENERATED FROM cmd_chdir.h.in.  DO NOT EDIT.

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


#ifndef _FS_SHELL__CMD_CHDIR_
#define _FS_SHELL__CMD_CHDIR_

// Optional command chdir

#ifdef USE_CMD_CHDIR


#include <unistd.h>
#include "globals.h"
#include "helpers.h"


/* from cmd_chdir.h.in:31 */
extern const char cmd_name_chdir[];
#define ENUM_LIST__CHDIR \
            /* from cmd_chdir.h.in:31 */ \
            COMMAND_INDEX__CHDIR,
#define VIRTUAL_ENUM_LIST__CHDIR
#define GLOBAL_VARDEF__CHDIR \
            /* from cmd_chdir.h.in:31 */ \
            const char cmd_name_chdir[] = "cd";
#define INITIALIZE__CHDIR \
            /* from cmd_chdir.h.in:31 */ \
            command_list_names[COMMAND_INDEX__CHDIR] = cmd_name_chdir;
#define STARTUP_CASE__CHDIR
#define RUN_CASE__CHDIR \
    case COMMAND_INDEX__CHDIR: \
        /* from cmd_chdir.h.in:31 */ \
            /* from cmd_chdir.h.in:32 */ \
        LOG(":: cd "); \
        LOGLN(global_arg); \
        global_err = chdir(global_arg); \
        break;
#define REQUIRES_ADDL_ARG__CHDIR

#else /* USE_CMD_CHDIR */

#define ENUM_LIST__CHDIR
#define VIRTUAL_ENUM_LIST__CHDIR
#define GLOBAL_VARDEF__CHDIR
#define INITIALIZE__CHDIR
#define STARTUP_CASE__CHDIR
#define RUN_CASE__CHDIR
#define REQUIRES_ADDL_ARG__CHDIR
#endif /* USE_CMD_CHDIR */

#endif /* _FS_SHELL__CMD_CHDIR_ */
