// GENERATED FROM cmd_pwd.h.in.  DO NOT EDIT.

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


#ifndef _FS_SHELL__CMD_PWD_
#define _FS_SHELL__CMD_PWD_

// Optional command pwd

#ifdef USE_CMD_PWD


#include <unistd.h>
#include "globals.h"
#include "helpers.h"

#ifndef PWD_BUFFER_SIZE
#define PWD_BUFFER_SIZE 4000
#endif


/* from cmd_pwd.h.in:35 */
extern const char cmd_name_pwd[];
#define ENUM_LIST__PWD \
            /* from cmd_pwd.h.in:35 */ \
            COMMAND_INDEX__PWD,
#define VIRTUAL_ENUM_LIST__PWD
#define GLOBAL_VARDEF__PWD \
            /* from cmd_pwd.h.in:35 */ \
            const char cmd_name_pwd[] = "pwd";
#define INITIALIZE__PWD \
            /* from cmd_pwd.h.in:35 */ \
            command_list_names[COMMAND_INDEX__PWD] = cmd_name_pwd; \
            /* from cmd_pwd.h.in:36 */ \
        char *pwd_str;
#define STARTUP_CASE__PWD
#define RUN_CASE__PWD \
    case COMMAND_INDEX__PWD: \
        /* from cmd_pwd.h.in:35 */ \
            /* from cmd_pwd.h.in:40 */ \
        /* libc4, libc5, glibc allows the buffer argument to be NULL and size to be 0,*/ \
        /* which means the library will allocate the string to as big as necessary.*/ \
        /* And we'll need to free the memory.  But this doesn't seem well supported.*/ \
        pwd_str = malloc(PWD_BUFFER_SIZE); \
        if (pwd_str == NULL) { \
            stderrP(helper_str__malloc_failed); \
            global_err = 1; \
        } else { \
            if (getcwd(pwd_str, PWD_BUFFER_SIZE) == NULL) { \
                global_err = 1; \
            } else if (strequal(global_arg, "-")) { \
                stdoutPLn(pwd_str); \
            } else { \
                setenv(global_arg, pwd_str, 1); \
            } \
            free(pwd_str); \
        } \
        break;
#define REQUIRES_ADDL_ARG__PWD

#else /* USE_CMD_PWD */

#define ENUM_LIST__PWD
#define VIRTUAL_ENUM_LIST__PWD
#define GLOBAL_VARDEF__PWD
#define INITIALIZE__PWD
#define STARTUP_CASE__PWD
#define RUN_CASE__PWD
#define REQUIRES_ADDL_ARG__PWD
#endif /* USE_CMD_PWD */

#endif /* _FS_SHELL__CMD_PWD_ */
