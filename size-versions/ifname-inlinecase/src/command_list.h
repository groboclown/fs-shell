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
#ifndef _FS_SHELL_COMMANDS_
#define _FS_SHELL_COMMANDS_

#include "uses.h"


// WARNING this enum must be identically matched with the lists
//   in command_list.c ; changes to the ordering or anything else
//   here must be identically reflected in the lists.
enum CommandIndex {
    // Each of these values is an index into the command list.

    // Required commands (not optionally built)

    // Find command is always the first entry, and, because
    // its string match is "" (empty), it means it always prevents the
    // virtual commands from matching.
    COMMAND_INDEX__FIND_CMD = 0,

    // Real commands
    COMMAND_INDEX__NOOP,
    COMMAND_INDEX__VERSION,

#ifdef USES_FMODE
    COMMAND_INDEX__FMODE,
#endif
#ifdef USE_CMD_ECHO
    // Each argument for echo is printed on its own line.
    COMMAND_INDEX__ECHO,
#endif
#ifdef USE_CMD_RM
    // Each argument to rm is a file to remove
    COMMAND_INDEX__RM,
#endif
#ifdef USE_CMD_RMDIR
    // Each argument to rmdir is a directory to remove
    COMMAND_INDEX__RMDIR,
#endif

#ifdef USE_CMD_TOUCH
    // The start sets up the execution, then runs the shared __RUN
    COMMAND_INDEX__TOUCH,
#endif
#ifdef USE_CMD_TRUNC
    // The start sets up the execution, then runs the shared __RUN
    COMMAND_INDEX__TRUNC,
#endif
#if defined(USE_CMD_TOUCH) || defined(USE_CMD_TRUNC)
    COMMAND_INDEX__TRUNC_TOUCH__RUN,
#endif

#ifdef USE_CMD_DUP_R
    // This runs the same as all other dup commands.
    //   - The setup creates the mode, then returns
    //     the COMMAND_INDEX__DUP__FD as the
    //     running command.
    COMMAND_INDEX__DUP_R,
#endif
#ifdef USE_CMD_DUP_W
    // This runs the same as all other dup commands.
    //   - The setup creates the mode, then returns
    //     the COMMAND_INDEX__DUP__FD as the
    //     running command.
    COMMAND_INDEX__DUP_W,
#endif
#ifdef USE_CMD_DUP_A
    // This runs the same as all other dup commands.
    //   - The setup creates the mode, then returns
    //     the COMMAND_INDEX__DUP__FD as the
    //     running command.
    COMMAND_INDEX__DUP_A,
#endif

#ifdef USES_DUP
    // This runs the same as all other dup commands.
    // First reads a file descriptor
    COMMAND_INDEX__DUP__FD,
    // Then reads the file/fd to dup to
    COMMAND_INDEX__DUP__TGT,
#endif

#ifdef USE_CMD_MKNOD
    // mknod first reads the node type argument, but
    // that's under COMMAND_INDEX__MKNOD_DEV__TYPE
    COMMAND_INDEX__MKNOD,
#endif
#ifdef USE_CMD_MKDEV
    // reads the device major
    COMMAND_INDEX__MKDEV,
    // then device minor
    COMMAND_INDEX__MKDEV__MINOR,
    // this then moves over to COMMAND_INDEX__MKNOD_DEV__TYPE
#endif
#ifdef USES_MKNOD
    // get the device type
    COMMAND_INDEX__MKNOD_DEV__TYPE,
    // create the node for each given file.
    COMMAND_INDEX__MKNOD_DEV__RUN,
#endif

#ifdef USE_CMD_MKDIR
    // mkdir creates each directory argument.
    COMMAND_INDEX__MKDIR,
#endif
#ifdef USE_CMD_CHOWN
    // chown first takes the owner ID
    COMMAND_INDEX__CHOWN,
    // then the group ID
    COMMAND_INDEX__CHOWN__GROUP,
    // then the list of files to change
    COMMAND_INDEX__CHOWN__RUN,
#endif
#ifdef USE_CMD_CHMOD
    // chmod first reads the file mode
    COMMAND_INDEX__CHMOD,
    // then changes the mode for each file
    COMMAND_INDEX__CHMOD__RUN,
#endif

#ifdef USE_CMD_LN_S
    // ln-s reads the source of the link then advances on its own for
    //   proper error detection on argument count.
    COMMAND_INDEX__LN_S,
#endif
#ifdef USE_CMD_LN_H
    // ln-h reads the source of the link then advances on its own for
    //   proper error detection on argument count.
    COMMAND_INDEX__LN_H,
#endif
#ifdef USE_CMD_MV
    // mv reads the source of the move then advances on its own for
    //   proper error detection on argument count.
    COMMAND_INDEX__MV,
#endif

#ifdef USE_CMD_SLEEP
    // sleep parses the argument as a numeric, and sleeps for that long.
    COMMAND_INDEX__SLEEP,
#endif
#ifdef USE_CMD_SIGNAL
    // signal reads numerics until the argument is "wait", at which
    //   point the numeric handling is stopped, no more args are allowed.
    COMMAND_INDEX__SIGNAL,
#endif

#ifdef USE_CMD_EXEC
    // exec is handled differently.  The setup is called but it never returns.
    COMMAND_INDEX__EXEC,
#endif

    // The error command is always last; it's a signal for the number of entries in the index.
    //   It also prevents odd errors for trailing commas.
    COMMAND_INDEX__ERR
};


// index -> command name for parsing ease.
// Some compilers generate bad memory addresses when this is a const char *[].
//   This fixed Nx9 array means there's wasted space for many commands, but it builds a
//   really easy structure for things to parse.  The alternative is a bit more memory
//   conservative, but is really funky to create correctly (at least I couldn't do it with
//   dietlibc).
// extern const void * const command_list_names_void[];
const char ** get_command_list_names();


#endif /* _FS_SHELL_COMMANDS_ */