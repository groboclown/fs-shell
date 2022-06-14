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

#ifndef _FS_SHELL__CMD_CHOWN_

// No startup execution
#define STARTUP__COMMAND_INDEX__CHOWN
#define STARTUP__COMMAND_INDEX__CHOWN__GROUP
#define STARTUP__COMMAND_INDEX__CHOWN__RUN


#ifdef USE_CMD_CHOWN
#include <sys/stat.h>

// store user in arg1, group in arg2

#define CASE__COMMAND_INDEX__CHOWN \
case COMMAND_INDEX__CHOWN: \
    LOG(":: chown reading owner id "); \
    LOGLN(global_arg); \
    global_cmd++; \
    global_arg1_i = helper_arg_to_uint(global_arg, 10, 0xffff); \
    if (global_arg1_i < 0) { \
        global_err = 1; \
        global_cmd = COMMAND_INDEX__ERR; \
    } \
    break;

#define CASE__COMMAND_INDEX__CHOWN__GROUP \
case COMMAND_INDEX__CHOWN__GROUP: \
    LOG(":: chown reading group id "); \
    LOGLN(global_arg); \
    global_cmd++; \
    global_arg2_i = helper_arg_to_uint(global_arg, 10, 0xffff); \
    if (global_arg2_i < 0) { \
        global_err = 1; \
        global_cmd = COMMAND_INDEX__ERR; \
    } \
    break;

#define CASE__COMMAND_INDEX__CHOWN__RUN \
case COMMAND_INDEX__CHOWN__RUN: \
    LOG(":: chown "); \
    LOGLN(global_arg); \
    global_err = chown(global_arg, global_arg1_i, global_arg2_i); \
    break;

#else /* USE_CMD_CHOWN */
#define CASE__COMMAND_INDEX__CHOWN
#define CASE__COMMAND_INDEX__CHOWN__GROUP
#define CASE__COMMAND_INDEX__CHOWN__RUN
#endif /* USE_CMD_CHOWN */

#endif /* _FS_SHELL__CMD_CHOWN_ */