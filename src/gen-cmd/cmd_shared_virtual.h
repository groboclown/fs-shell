// GENERATED FROM cmd_shared_virtual.h.in.  DO NOT EDIT.

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
SOFTWARE.
*/

#ifndef _FS_SHELL__CMD_SHARED_VIRTUAL_
#define _FS_SHELL__CMD_SHARED_VIRTUAL_


// Many commands reuse the same basic argument parsing functionality.
// This captures that.
//
// These assign a global variable the parsed argument, then redirect
// the next arg processing to what is set in global_arg3_i
//
// COMMAND_INDEX__SHARED_STR - store arg into global_arg
// COMMAND_INDEX__SHARED_INT - store arg into global_arg2_i

// Optional command shared_str

#ifdef USES_SHARED_STR




#define ENUM_LIST__SHARED_STR
#define VIRTUAL_ENUM_LIST__SHARED_STR \
            /* from cmd_shared_virtual.h.in:36 */ \
            COMMAND_INDEX__SHARED_STR,
#define GLOBAL_VARDEF__SHARED_STR
#define INITIALIZE__SHARED_STR
#define STARTUP_CASE__SHARED_STR
#define RUN_CASE__SHARED_STR \
    case COMMAND_INDEX__SHARED_STR: \
        /* from cmd_shared_virtual.h.in:36 */ \
            /* from cmd_shared_virtual.h.in:38 */ \
            LOG(":: storing "); \
            LOGLN(global_arg); \
            global_arg_cached = global_arg; \
            global_cmd = global_arg3_i; \
        break;
#define REQUIRES_ADDL_ARG__SHARED_STR \
            case COMMAND_INDEX__SHARED_STR:

#else /* USES_SHARED_STR */

#define ENUM_LIST__SHARED_STR
#define VIRTUAL_ENUM_LIST__SHARED_STR
#define GLOBAL_VARDEF__SHARED_STR
#define INITIALIZE__SHARED_STR
#define STARTUP_CASE__SHARED_STR
#define RUN_CASE__SHARED_STR
#define REQUIRES_ADDL_ARG__SHARED_STR
#endif /* USES_SHARED_STR */


// Optional command shared_int

#ifdef USES_SHARED_INT




#define ENUM_LIST__SHARED_INT
#define VIRTUAL_ENUM_LIST__SHARED_INT \
            /* from cmd_shared_virtual.h.in:51 */ \
            COMMAND_INDEX__SHARED_INT2,
#define GLOBAL_VARDEF__SHARED_INT
#define INITIALIZE__SHARED_INT
#define STARTUP_CASE__SHARED_INT
#define RUN_CASE__SHARED_INT \
    case COMMAND_INDEX__SHARED_INT2: \
        /* from cmd_shared_virtual.h.in:51 */ \
            /* from cmd_shared_virtual.h.in:53 */ \
            LOG(":: storing int "); \
            LOGLN(global_arg); \
            tmp_val = helper_arg_to_uint(global_arg, 10, 0xffff); \
            if (tmp_val < 0) { \
                global_err = 1; \
                global_cmd = COMMAND_INDEX__ERR; \
                break; \
            } \
            global_arg2_i = tmp_val; \
            global_cmd = global_arg3_i; \
        break;
#define REQUIRES_ADDL_ARG__SHARED_INT \
            case COMMAND_INDEX__SHARED_INT2:

#else /* USES_SHARED_INT */

#define ENUM_LIST__SHARED_INT
#define VIRTUAL_ENUM_LIST__SHARED_INT
#define GLOBAL_VARDEF__SHARED_INT
#define INITIALIZE__SHARED_INT
#define STARTUP_CASE__SHARED_INT
#define RUN_CASE__SHARED_INT
#define REQUIRES_ADDL_ARG__SHARED_INT
#endif /* USES_SHARED_INT */


// Optional command shared_itoa

#ifdef USES_SHARED_ITOA



// buffer must be global_itoa.  return should be stored in global_itoa_ptr
char *shared_itoa(int value, char *buffer) {
    // size of global_itoa == (3 * sizeof(int)) + 1, but we want to
    // write to -1 first, so...
    char *itoa_ptr = buffer + (3 * sizeof(int));
    int is_negative = 0;
    *itoa_ptr = '\0';
    if (value < 0) {
        is_negative = 1;
        value = 0 - value;
    }
    // Do-while allows us to add the 0 if the value is zero.
    do {
        itoa_ptr -= sizeof(char);
        *itoa_ptr = '0' + (value % 10);
        value /= 10;
    } while (value);
    if (is_negative) {
        itoa_ptr -= sizeof(char);
        *itoa_ptr = '-';
    }
    return itoa_ptr;
}




#define ENUM_LIST__SHARED_ITOA
#define VIRTUAL_ENUM_LIST__SHARED_ITOA \
            /* from cmd_shared_virtual.h.in:98 */ \
            COMMAND_INDEX__DO_NOT_USE_ITOA,
#define GLOBAL_VARDEF__SHARED_ITOA
#define INITIALIZE__SHARED_ITOA \
            /* from cmd_shared_virtual.h.in:100 */ \
            char global_itoa[(3 * sizeof(int)) + 1]; \
            char *global_itoa_ptr;
#define STARTUP_CASE__SHARED_ITOA
#define RUN_CASE__SHARED_ITOA
#define REQUIRES_ADDL_ARG__SHARED_ITOA

#else /* USES_SHARED_ITOA */

#define ENUM_LIST__SHARED_ITOA
#define VIRTUAL_ENUM_LIST__SHARED_ITOA
#define GLOBAL_VARDEF__SHARED_ITOA
#define INITIALIZE__SHARED_ITOA
#define STARTUP_CASE__SHARED_ITOA
#define RUN_CASE__SHARED_ITOA
#define REQUIRES_ADDL_ARG__SHARED_ITOA
#endif /* USES_SHARED_ITOA */


#if defined(USES_SHARED_STR) || defined(USES_SHARED_INT) || defined(USES_SHARED_ITOA)

// Nothing extra here.

#define ENUM_LIST__SHARED_VIRTUAL \
            ENUM_LIST__SHARED_STR \
            ENUM_LIST__SHARED_INT \
            ENUM_LIST__SHARED_ITOA
#define VIRTUAL_ENUM_LIST__SHARED_VIRTUAL \
            VIRTUAL_ENUM_LIST__SHARED_STR \
            VIRTUAL_ENUM_LIST__SHARED_INT \
            VIRTUAL_ENUM_LIST__SHARED_ITOA
#define GLOBAL_VARDEF__SHARED_VIRTUAL \
            GLOBAL_VARDEF__SHARED_STR \
            GLOBAL_VARDEF__SHARED_INT \
            GLOBAL_VARDEF__SHARED_ITOA
#define INITIALIZE__SHARED_VIRTUAL \
            INITIALIZE__SHARED_STR \
            INITIALIZE__SHARED_INT \
            INITIALIZE__SHARED_ITOA
#define STARTUP_CASE__SHARED_VIRTUAL \
            STARTUP_CASE__SHARED_STR \
            STARTUP_CASE__SHARED_INT \
            STARTUP_CASE__SHARED_ITOA
#define RUN_CASE__SHARED_VIRTUAL \
            RUN_CASE__SHARED_STR \
            RUN_CASE__SHARED_INT \
            RUN_CASE__SHARED_ITOA
#define REQUIRES_ADDL_ARG__SHARED_VIRTUAL \
            REQUIRES_ADDL_ARG__SHARED_STR \
            REQUIRES_ADDL_ARG__SHARED_INT \
            REQUIRES_ADDL_ARG__SHARED_ITOA

#else /* defined(USES_SHARED_STR) || defined(USES_SHARED_INT) || defined(USES_SHARED_ITOA) */

#define ENUM_LIST__SHARED_VIRTUAL
#define VIRTUAL_ENUM_LIST__SHARED_VIRTUAL
#define GLOBAL_VARDEF__SHARED_VIRTUAL
#define INITIALIZE__SHARED_VIRTUAL
#define STARTUP_CASE__SHARED_VIRTUAL
#define RUN_CASE__SHARED_VIRTUAL
#define REQUIRES_ADDL_ARG__SHARED_VIRTUAL
#endif /* defined(USES_SHARED_STR) || defined(USES_SHARED_INT) || defined(USES_SHARED_ITOA) */


#endif /* _FS_SHELL__CMD_SHARED_VIRTUAL_ */
