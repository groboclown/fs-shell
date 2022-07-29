// GENERATED FROM cmd_export.h.in.  DO NOT EDIT.

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

#ifndef _FS_SHELL__CMD_EXPORT_
#define _FS_SHELL__CMD_EXPORT_

// Optional command export

#ifdef USE_CMD_EXPORT



/* from cmd_export.h.in:26 */
extern const char cmd_name_export[];
#define ENUM_LIST__EXPORT \
            /* from cmd_export.h.in:26 */ \
            COMMAND_INDEX__EXPORT,
#define VIRTUAL_ENUM_LIST__EXPORT
#define GLOBAL_VARDEF__EXPORT \
            /* from cmd_export.h.in:26 */ \
            const char cmd_name_export[] = "export";
#define INITIALIZE__EXPORT \
            /* from cmd_export.h.in:26 */ \
            command_list_names[COMMAND_INDEX__EXPORT] = cmd_name_export;
#define STARTUP_CASE__EXPORT \
    case COMMAND_INDEX__EXPORT: \
        /* from cmd_export.h.in:26 */ \
            /* from cmd_export.h.in:27 */ \
        /* Call the shared store to capture the next argument.*/ \
        global_cmd = COMMAND_INDEX__SHARED_STR; \
        global_arg3_i = COMMAND_INDEX__EXPORT; \
        break;
#define RUN_CASE__EXPORT \
    case COMMAND_INDEX__EXPORT: \
        /* from cmd_export.h.in:26 */ \
            /* from cmd_export.h.in:33 */ \
        /* Called after the first argument was captured, and now*/ \
        /* on the second argument.*/ \
        LOG(":: export env "); \
        LOG(global_arg_cached); \
        LOG(" as "); \
        LOGLN(global_arg); \
        global_err = setenv(global_arg_cached, global_arg, 1); \
        /* Doesn't make sense to assign new values to the same name.*/ \
        global_cmd = COMMAND_INDEX__ERR; \
        break;
#define REQUIRES_ADDL_ARG__EXPORT

#else /* USE_CMD_EXPORT */

#define ENUM_LIST__EXPORT
#define VIRTUAL_ENUM_LIST__EXPORT
#define GLOBAL_VARDEF__EXPORT
#define INITIALIZE__EXPORT
#define STARTUP_CASE__EXPORT
#define RUN_CASE__EXPORT
#define REQUIRES_ADDL_ARG__EXPORT
#endif /* USE_CMD_EXPORT */

#endif /* _FS_SHELL__CMD_EXPORT_ */
