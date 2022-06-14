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


#include "uses.h"
#include "output.h"
#include "args.h"
#include "globals.h"
#include "command_runner.h"
#include "command_list.h"
#include "helpers.h"
#include "version.h"

// ==========================================================================
// Each supported command 
#include "cmd_noop.inc.h"
#include "cmd_version.inc.h"
#include "cmd_fmode.inc.h"
#include "cmd_echo.inc.h"
#include "cmd_rm.inc.h"
#include "cmd_rmdir.inc.h"
#include "cmd_touch_trunc.inc.h"
#include "cmd_dup.inc.h"
#include "cmd_mknod_mkdev.inc.h"
#include "cmd_mkdir.inc.h"
#include "cmd_chown.inc.h"
#include "cmd_chmod.inc.h"
#include "cmd_ln_mv.inc.h"
#include "cmd_sleep.inc.h"
#include "cmd_signal.inc.h"
#include "cmd_exec.inc.h"


// command_runner runs the commands over the parsed arguments.
//   returns the error code.
int command_runner() {
    // ======================================================================
    // Command runner internal variables
    int _err_count = 0;
    int _idx;

    // ======================================================================
    // "global" variables
    //    These are shared between the command runner and the commands.
    int global_err = 0;
    int global_arg1_i = 0;
    int global_arg2_i = 0;
    int global_arg3_i = 0;

    const char **command_list_names = get_command_list_names();

    // General use argument storage value
    const char *global_arg_cached = NULL;

    // there is also the "true" global const char *global_invoked_name;

    // Current argument value
    const char *global_arg;

#ifdef USES_SIGNALS
    sigset_t global_signal_set;
#endif

    // Current command name.
    const char *global_cmd_name = NULL;

    // Current command index.
    //   This can change while the cmd_name should remain the same.
    //   Set to COMMAND_INDEX__FIND_CMD to mean "searching for a command"
    int global_cmd = COMMAND_INDEX__FIND_CMD;

#ifdef USES_FMODE
    // Global file mode.  Set by the fmode command, but used by all kinds of
    //   commands.
    int global_fmode = 0644;
#endif

#ifdef USE_CMD_EXEC
    char *exec_arg3 = NULL;
    const char **exec_argv = NULL;
#endif


    // ======================================================================
    // Argument Parsing Loop
    global_arg = args_advance_token();
    while (global_arg != NULL) {
        // This is a long if/else block until error checking.

        // ==================================================================
        // Check end-of-command first.
        //   This allows recognizing "; ;" as okay.

        if (strequal("&&", global_arg)) {
            if (_err_count > 0) {
                // && with errors stops the shell.
                stderrP("FAIL &&\n");
                break;
            }
            LOG(":: &&\n");
            global_cmd = COMMAND_INDEX__FIND_CMD;
        } else

        if (strequal(";", global_arg)) {
            // ";" ignores any errors, resetting the error count.
            LOG(":: ;\n");
            _err_count = 0;
            global_cmd = COMMAND_INDEX__FIND_CMD;
        } else {
            // Default to no error.
            global_err = 0;

            switch (global_cmd) {
                // ==========================================================
                // Find the invoked command.
                case COMMAND_INDEX__FIND_CMD:
                    global_cmd_name = global_arg;

                    if (global_arg[0] == 0) {
                        // special placeholder
                        global_cmd = COMMAND_INDEX__FIND_CMD;
                    }

                    STARTUP__COMMAND_INDEX__NOOP
                    STARTUP__COMMAND_INDEX__VERSION
                    STARTUP__COMMAND_INDEX__FMODE
                    STARTUP__COMMAND_INDEX__ECHO
                    STARTUP__COMMAND_INDEX__RM
                    STARTUP__COMMAND_INDEX__RMDIR
                    STARTUP__COMMAND_INDEX__TOUCH
                    STARTUP__COMMAND_INDEX__TRUNC
                    STARTUP__COMMAND_INDEX__TRUNC_TOUCH__RUN
                    STARTUP__COMMAND_INDEX__DUP_R
                    STARTUP__COMMAND_INDEX__DUP_W
                    STARTUP__COMMAND_INDEX__DUP_A
                    STARTUP__COMMAND_INDEX__DUP__FD
                    STARTUP__COMMAND_INDEX__DUP__TGT
                    STARTUP__COMMAND_INDEX__MKNOD
                    STARTUP__COMMAND_INDEX__MKDEV
                    STARTUP__COMMAND_INDEX__MKDEV__MINOR
                    STARTUP__COMMAND_INDEX__MKNOD_DEV__TYPE
                    STARTUP__COMMAND_INDEX__MKNOD_DEV__RUN
                    STARTUP__COMMAND_INDEX__MKDIR
                    STARTUP__COMMAND_INDEX__CHOWN
                    STARTUP__COMMAND_INDEX__CHOWN__GROUP
                    STARTUP__COMMAND_INDEX__CHOWN__RUN
                    STARTUP__COMMAND_INDEX__CHMOD
                    STARTUP__COMMAND_INDEX__CHMOD__RUN
                    STARTUP__COMMAND_INDEX__LN_S
                    STARTUP__COMMAND_INDEX__LN_S__RUN
                    STARTUP__COMMAND_INDEX__LN_H
                    STARTUP__COMMAND_INDEX__LN_H__RUN
                    STARTUP__COMMAND_INDEX__MV
                    STARTUP__COMMAND_INDEX__MV__RUN
                    STARTUP__COMMAND_INDEX__SLEEP
                    STARTUP__COMMAND_INDEX__SIGNAL
                    STARTUP__COMMAND_INDEX__EXEC
                    // STARTUP__COMMAND_INDEX__ERR
                    
                    else {
                        LOG(":: command not matched: ");
                        LOGLN(global_arg);
                        global_cmd = COMMAND_INDEX__ERR;
                        global_err = 1;
                    }
                    break;

                // Virtual command, never exists here.
                // CASE__COMMAND_INDEX__FIND_CMD

                CASE__COMMAND_INDEX__NOOP
                CASE__COMMAND_INDEX__VERSION
                CASE__COMMAND_INDEX__FMODE
                CASE__COMMAND_INDEX__ECHO
                CASE__COMMAND_INDEX__RM
                CASE__COMMAND_INDEX__RMDIR
                CASE__COMMAND_INDEX__TOUCH
                CASE__COMMAND_INDEX__TRUNC
                CASE__COMMAND_INDEX__TRUNC_TOUCH__RUN
                CASE__COMMAND_INDEX__DUP_R
                CASE__COMMAND_INDEX__DUP_W
                CASE__COMMAND_INDEX__DUP_A
                CASE__COMMAND_INDEX__DUP__FD
                CASE__COMMAND_INDEX__DUP__TGT
                CASE__COMMAND_INDEX__MKNOD
                CASE__COMMAND_INDEX__MKDEV
                CASE__COMMAND_INDEX__MKDEV__MINOR
                CASE__COMMAND_INDEX__MKNOD_DEV__TYPE
                CASE__COMMAND_INDEX__MKNOD_DEV__RUN
                CASE__COMMAND_INDEX__MKDIR
                CASE__COMMAND_INDEX__CHOWN
                CASE__COMMAND_INDEX__CHOWN__GROUP
                CASE__COMMAND_INDEX__CHOWN__RUN
                CASE__COMMAND_INDEX__CHMOD
                CASE__COMMAND_INDEX__CHMOD__RUN

                // ln-s, ln-h, and mv have a common body
                //   without this, there's a terrible complexity
                //   that happens in the code.
                CASE__COMMAND_INDEX__LN_S
                CASE__COMMAND_INDEX__LN_H
                CASE__COMMAND_INDEX__MV
                CASE__COMMAND_INDEX__LN_MV_COMMON_BODY
                CASE__COMMAND_INDEX__LN_S_BODY
                CASE__COMMAND_INDEX__LN_H_BODY
                CASE__COMMAND_INDEX__MV_BODY
                CASE__COMMAND_INDEX__LN_MV_COMMON_BODY_END

                CASE__COMMAND_INDEX__SLEEP
                CASE__COMMAND_INDEX__SIGNAL
                CASE__COMMAND_INDEX__EXEC

                case COMMAND_INDEX__ERR:
                    global_err = 1;
                    break;
            }
        }

        // ==================================================================
        // Error checking.
        if (global_err != 0) {
            // Could use fprintf, but let's get smaller.
            stderrP("ERROR ");
            stderrP(global_cmd_name);
            stderrP(": ");
            stderrPLn(global_arg);
            _err_count++;
        }

        // advance.
        global_arg = args_advance_token();
    }
    return _err_count;
}
