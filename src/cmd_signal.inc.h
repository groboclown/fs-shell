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

#ifndef _FS_SHELL__CMD_SIGNAL_

#define NAME__SIGNAL "signal"

#ifdef USE_CMD_SIGNAL

#include <signal.h>

void signal_empty_handler(int signal) {
    LOG(":: handled signal\n");
}

#define STARTUP__COMMAND_INDEX__SIGNAL \
case COMMAND_INDEX__SIGNAL: \
    sigemptyset(&global_signal_set); \
    break;


#define CASE__COMMAND_INDEX__SIGNAL \
case COMMAND_INDEX__SIGNAL: \
    /* The "wait" string indicates the end of the signals. */ \
    if (strequal("wait", global_arg)) { \
        LOG(":: start signal wait\n"); \
        /* Early POSIX Draft 6 has sigwait() return the signal number. */ \
        /* New standard has sigwait() return 0 for no error, or the error number. */ \
        /* Dietlibc uses the old return code. */ \
        /* There's a small chance that an error occurs and that error code */ \
        /*   matches the signal. */ \
        global_arg1_i = 0; \
        global_err = sigwait(&global_signal_set, &global_arg1_i); \
/*#ifdef DEBUG */ \
/*printf(":: sigwait() returned %i, signal %i\n", global_err, global_arg1_i);*/ \
/*#endif*/ \
        if (global_err != 0 && global_err != global_arg1_i) { \
            /* Due to the initialization and the old way of working, */ \
            /*   this situation means that this is a real error situation. */ \
            global_err = 1; \
        } else { \
            /* Looks like a success. */ \
            global_err = 0; \
        } \
        LOG(":: wait complete\n"); \
        /* it doesn't make sense to keep parsing signals at this point. */ \
        global_cmd = COMMAND_INDEX__ERR; \
        break; \
    } \
    /* "wait" hasn't been found yet, so each argument is a */ \
    /* signal number. */ \
    global_arg1_i = helper_arg_to_uint(global_arg, 10, 0xffff); \
    if (global_arg1_i < 0) { \
        global_err = 1; \
        /* Do not allow the signal to wait.  This can lead an invalid operations. */ \
        global_cmd = COMMAND_INDEX__ERR; \
        break; \
    } \
    LOG(":: signal "); \
    LOGLN(global_arg); \
    sigaddset(&global_signal_set, global_arg1_i); \
    signal(global_arg1_i, &signal_empty_handler); \
    break;

#else /* USE_CMD_SIGNAL */
#define STARTUP__COMMAND_INDEX__SIGNAL
#define CASE__COMMAND_INDEX__SIGNAL
#endif /* USE_CMD_SIGNAL */
#endif /* _FS_SHELL__CMD_SIGNAL_ */
