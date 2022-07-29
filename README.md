# Precision Shell (presh)

[![Build](https://github.com/groboclown/precision-shell/actions/workflows/build.yml/badge.svg)](https://github.com/groboclown/precision-shell/actions/workflows/build.yml)

## Custom Built Shell With Only What You Need

Sometimes, you don't need or want a full fledged shell.  You just have a few things that you need to do, and allowing more is a security issue.

`presh` offers a [few commands and shell syntax](#what-it-does), and gives you the flexibility to select which ones to compile, which can make the executable smaller and provide extra security by not enabling commands that don't need to be run.  It's not POSIX conformant, and doesn't try to be.

The tool has two goals - provide just enough commands for what you need to do, and make it small.

Last build size:

* Do-nothing build:
  * glibc (Ubuntu): 819,656 bytes
  * glibc (Arch): 778,280 bytes
  * musl (Alpine): 21,944 bytes
  * dietlibc (Alpine): 13,256 bytes
* Minimal build:
  * glibc: 823,752 bytes
  * glibc (Arch): 778,280 bytes
  * musl (Alpine): 21,944 bytes
  * dietlibc (Alpine): 17,352 bytes
* Standard buld:
  * glibc (Ubuntu): 831,944 bytes
  * glibc (Arch): 782,376 bytes
  * musl (Alpine): 26,040 bytes
  * dietlibc (Alpine): 17,352 bytes
* Full build:
  * glibc (Ubuntu): 831,944 bytes
  * glibc (Arch): 786,472 bytes
  * musl (Alpine): 30,136 bytes
  * dietlibc (Alpine): 21,448 bytes

*dietlibc [requires](https://www.fefe.de/dietlibc/FAQ.txt) that you either not distribute the compiled executable, or release the executable under GPL v2.*

These file sizes are *statically compiled*, so they don't have any external dependencies other than the Linux OS.


## What It Does

The shell supports these commands:

* [version](#version) - prints the current version (cannot be disabled).
* [noop](#noop) - do nothing.  The comment command.
* [echo](#echo) - send text to `stdout`.
* [?:](#conditional-command) - run a command conditionally based on the error result of another.
* [subcmd](#subcmd) - run an argument as a complete precision shell command.
* [exit](#exit) - exits the command (or sub-command) with an exit code.
* [cd](#cd) - change current working directory.
* [pwd](#pwd) - display current working directory, or store it in an environment variable.
* [fmode](#fmode) - set the octal file mode for other commands.
* [rm](#rm) - remove files.
* [rmdir](#rmdir) - remove empty directories.
* [mv](#mv) - move a file from one name to another.
* [fmode](#fmode) - set a default file permission.
* [mkdir](#mkdir) - create an empty directory.
* [chmod](#chmod) - change file permissions.
* [chown](#chown) - change user and group owner for files.
* [ln-s](#ln-s) - create a symbolic link.
* [ln-h](#ln-h) - create a hard link.
* [sleep](#sleep) - wait for a number of seconds.
* [mknod](#mknod) - create a FIFO or UNIX socket node.
* [mkdev](#mkdev) - create a device OS node.
* [touch](#touch) - <strike>Update the access and modification times of each file to the current time, or,</strike> if a file does not exist, it is created empty.
* [trunc](#trunc) - Sets the file length to 0, and if the file does not exist, creates it.
* [dup-r, dup-w, dup-a](#dup) - duplicates a file to a file descriptor for the remaining commands in this execution.
* [export](#export) - export an environment variable + value into the running process and to-be-run child processes.
* [signal .. wait](#signal-wait) - wait for an OS signal before continuing.
* [exec](#exec) - switch execution to a new process.
* [spawn](#spawn) - launch a new process in the background.
* [wait-pid](#wait-pid) - wait for a process started by `spawn` to end.
* [kill-pid](#kill-pid) - send a signal to a process.

It also supports:
* [Embedded Quoting](#command-parsing) by using the `[` and `]` symbols to allow easy deep quotes, like `exec [/usr/bin/echo [from native echo]]`
* [Chaining commands](#command-chaining) together with `&&` and `;` (cannot be disabled).
* [Standard script argument flag](#standard-script-flag) - if passed with the arguments `-c "commands"`, then the shell will parse the commands argument into individual commands (cannot be disabled).
* [Script files](#script-files) - as an argument if used with `-f script-file-name`.
* [Commands from stdin](#passing-commands-from-stdin) - With the `-` argument, commands are parsed from stdin.  **Without the streaming input flag, the shell will not read from stdin.**
* [Environment variable parsing](#environment-variables) - the input values can be replaced with environment variables, when specified in the form `${VALUE}` (the standard shell form of `$VALUE` is not supported).

`presh` works very well for Docker and Podman containers as the default shell, which is useful if you need file modifications to an image that has no shell.

```Dockerfile
FROM super-skinny-image:11.12

COPY presh /bin/sh

# Because /bin/sh is now the shell, run commands will
#   run through it by executing "/bin/sh -c (arguments)"
RUN echo Startup \
    && rm /www/404.html /www/501.html \
    && rmdir /tmp \
    echo Complete
```


## What It Doesn't Do

* List files or file details.
* Copy files.
* Report detailed error messages.
* Change file timestamps.
* Provide splat pattern replacements.
* Looping
* Anything with the network.
* Tell you how to use it.  That's what this document is for.


## Why Would I Need It?

The tool was built with container (Docker and Podman) images that use minimal OS resources.  Golang projects commonly build a single file, the executable, placed into a `FROM scratch` image.  In these environments, `presh` can be easily added to provide some minimal file manipulation.

Additionally, you can build the tool with exactly the commands you need to run.  This limits the attack surface, making your install just that much safer.

See [sample.Dockerfile](sample.Dockerfile) for an example of using it with Docker and a `FROM scratch`, to show that no OS setup is necessary to run the shell.


## How Do I Get It?

Because of the goals for the shell, no compiled version is distributed.  You're expected to build it from source yourself.

You can build it directly and set the included commands:

```bash
make "COMMAND_FLAGS=-DUSE_CMD_CHMOD -DUSE_STREAMING_INPUT"
```

Flags are split into command flags and usage flags.  Each [command](#help) in this document also includes the flag to enable it in the compiled executable.  A complete list of flags is in the [`Makefile.command-flags`](Makefile.command-flags) file.

You can use some built-in command flag groups:

* `make INCLUDE_ALL_COMMANDS=1` - build with all supported commands.
* `make INCLUDE_STANDARD_COMMANDS=1` - include some simple file operations, streaming input, sleep, and signal handling.
* `make INCLUDE_MINIMAL_COMMANDS=1` - include symbolic links, mkdir, echo, chown, and chmod.

The commands that cannot be directly controlled for inclusion are:

* `version` - this is always included.
* `fmode` - this is automatically included for `mkdir`, `touch`, `trunc`, and the `dup` commands.

To run the build, you'll need basic C compiler, linker, and make.  If you have Python 3 installed, you can generate the command source files (they are bundled if you don't have it).

The most common setup is to build it inside a Docker container for use in another container.  See [`Dockerfile`](Dockerfile) for how this is done.


## Help

All commands and special build modes are described here.  To add in a compile flag, run the build like: `make COMMAND_FLAGS="-DUSE_CMD_ECHO -DUSE_CMD_RM"`


### version

**Compile flag**: *always present*

**Usage**: `version`

Prints the version information to stdout.  Any additional arguments generates an error.

### noop

**Compile flag**: `-DUSE_CMD_NOOP`

**Usage**: `noop [arg1 [arg2 ...]]`

**Usage**: `# [Some comment text.  Put inside quoting to protect against && and ;]`

**Usage**: `#! /shebang/format/presh -f`

Does nothing and ignores all arguments after it.  When used as a comment, it's best to enclose the comment inside quotes to protect against `&&` and `;`, which the shell will interpret as an end-of-command.

The noop can also be used to mask a file start shebang (`#!`) marker.  To work with presh, the precise format will need a space after the shebang mark, and include the `-f` argument to have the script be interpreted as a file.  This mode requires the [stream input flag](#script-files).

**Example 1:**

A script file.

```bash
#! /usr/bin/presh -f

echo [This is a script file.]
```

### echo

**Compile flag**: `-DUSE_CMD_ECHO`

**Usage**: `echo [str1 [str2 ...]]`

Sends to `stdout` each argument, one per line.  To have a multi-word statement on a single line, it must be passed as a single argument; see (Command Parsing)[#command-parsing] for details.

# Conditional Command

**Compile flag**: `-DUSE_CMD_CONDITIONAL`

**Usage**: `?: (conditional cmd) (if successful) [if failure]`

Runs the first argument as a full presh command, as though it was run through [`subcmd`](#subcmd).  If the exit code is zero, then the second argument is run as a full presh command).  If the first argument fails, then the third argument runs, or is skipped if it isn't given.


**Example 1:**

Test to make sure that [`chmod`](#chmod) correctly makes things not-writable.

```bash
$ presh -c "\
  touch /tmp/file && \
  chmod 000 /tmp/file && \
  ?: [touch /tmp/file] \
      [echo [chmod is dumb]] \
      [echo [chmod works]]"
ERROR touch: /tmp/file
chmod works
```

**Example 2:**

Because precision shell [does not support `||` chaining](#chaining-commands), this can be simulated by using the conditional operation with the [`noop`](#noop) command.

```bash
presh -c "\
  dup 2 /dev/null ;
  ?: [touch [/usr/bin/check-config my-config.rc]] \
      noop \
      [exec /usr/bin/generate-default-config my-config.rc]
  "
```

### subcmd

**Compile flag**: `-DUSE_CMD_SUBCMD`

**Usage**: `subcmd [command as an argument [command ...]]`

Runs each argument as a whole command.

**Example:**

```bash
presh -c "\
  touch /tmp/file && \
  subcmd [\
    ln-s /tmp/file /tmp/foo && \
    ln-s /tmp/file /tmp/bar \
  ] ; \
  echo done"
```

### exit

**Compile flag**: `-DUSE_CMD_EXIT`

**Usage**: `exit (exit code)`

Quits the execution of the current command context with an exit code, and no other commands are parsed.  If the exit is within a sub-command, then the sub command exits.

**Example:**

```bash
presh -c "subcmd [exit 1] && echo [should not run]"
```

### cd

**Compile flag**: `-DUSE_CMD_CD`

**Usage**: `cd (directory)`

Changes the current directory.  Useful for relative paths when running file commands, or when launching an executable to run inside a specific directory.

### pwd

**Compile flag**: `-DUSE_CMD_PWD`

**Usage**: `pwd -`

**Usage**: `pwd (env variable name)`

When used with the argument `-`, the current working directory is written to stdout on its own line.  Otherwise, the environment variable name argument has the current working directory path stored in its value.

Multiple arguments can be given, where the same rules apply for each argument.

### rm

**Compile flag**: `-DUSE_CMD_RM`

**Usage**: `rm [file1 [file2 ...]]`

Removes each file passed as an argument.  The command will attempt to remove each file, and if any of them fail, then the whole command fails with an exit code equal to the sum of the error codes.

### rmdir

**Compile flag**: `-DUSE_CMD_RMDIR`

**Usage**: `rmdir [dir1 [dir2 ...]]`

Removes each empty directory passed as an argument.  If a directory is not empty, the command will fail.  The command will attempt to remove each directory, and if any of them fail, then the whole command fails with an exit code equal to the sum of the number of failed files.

### mv

**Compile flag**: `-DUSE_CMD_MV`

**Usage**: `mv (src file) (target file)`

Renames the file referenced by the first argument to a new name referenced by the second argument.  If the operation fails, or if there is no second argument, then the command fails with an exit code of 1.

### fmode

**Compile flag**: *included automatically if the dependent commands are included; see below*

**Usage**: `fmode (octal mode)`

Changes an internal default file mode value to the given octal mode.  If never set, the default file mode value is `0644`.

Example:

```bash
$ presh -c "fmode 765 ; touch a.txt"
$ ls -l a.txt
-rwxrw-r-x 1 user user   0 Jan 19 09:51 a.txt 
```

This can include the higher bits, too, so that some commands that support it (and if the executing user has permissions to run it) can set the sticky bits.

This command is added if any of these commands are added through compile flags, and they will in turn use this mode when working with files.

* [`mkdir`](#mkdir)
* [`touch`](#touch)
* [`trunc`](#trunc)
* [`mknod`](#mknod)
* [`mkdev`](#mkdev)
* [`dup-a`](#dup-a)
* [`dup-r`](#dup-r)
* [`dup-w`](#dup-w)

### mkdir

**Compile flag**: `-DUSE_CMD_MKDIR`

**Usage**: `mkdir [file1 [file2 ...]]`

Creates the listed directories.  The parent directory must exist, or it will generate an error.  If any creation fails, then the command fails with the number of failed directories.

Each directory is created with the global file mode (see [`fmode`](#fmode)), with the user, group, and other executable flags also set.  To change this to something else, a [`chmod`](#chmod) must be run.

### chmod

**Compile flag**: `-DUSE_CMD_CHMOD`

**Usage**: `chmod (octal mode) [file1 [file2 ...]]`

Changes the file permissions for each file or directory.  The mode must be passed as an octal number.

Example:

```bash
$ touch a.txt
$ chmod 600 a.txt
$ ls -l a.txt
-rw------- 1 user user   0 Jan 19 09:51 a.txt
$ presh -c "chmod 770 a.txt"
$ ls -l a.txt
-rwxrwx--- 1 user user   0 Jan 19 09:51 a.txt
```

This command will fail if the mode value is out of range or not a number.

### chown

**Compile flag**: `-DUSE_CMD_MKDIR`

**Usage**: `chown (uid) (gid) [file1 [file2 ...]]`

Changes the owner and group ID for each file, directory, or symlink argument.

### ln-s

**Compile flag**: `-DUSE_CMD_LN_S`

**Usage**: `ln-s (src file) (dest file)`

Creates a symbolic link named dest file, pointing to src file.

### ln-h

**Compile flag**: `-DUSE_CMD_LN_H`

**Usage**: `ln-h (src file) (dest file)`

Creates a hard link named dest file, pointing to src file.

### sleep

**Compile flag**: `-DUSE_CMD_SLEEP`

**Usage**: `sleep [seconds [seconds ...]]`

Sleeps for the number of seconds in the argument.  If no arguments are given, or if an argument is not a positive integer, then it does nothing (no error).  If multiple, positive integers are given, then it sleeps for the sum of them.

### mknod

**Compile flag**: `-DUSE_CMD_MKNOD`

**Usage**: `mknod (node type) [file1 [file2 ...]]`

Creates a special or ordinary file of the given type.  The node type is OS specific, but in general, the values supported are:

* `p` - pipe (FIFO queue)
* `s` - UNIX domain socket

The created file will have the file permissions set in [`fmode`](#fmode).

### mkdev

**Compile flag**: `-DUSE_CMD_MKDEV`

**Usage**: `mkdev (major version) (minor version) (node type) [file1 [file2 ...]]`

The node type can be one of these:

* `b` - block device
* `c` and `u` - character device

The major and minor version reflect the OS kernel specific device number.

For example, to create the standard `/dev/null` device, you would run:

```bash
presh mkdev c 1 3 /dev/null
```

The created file will have the file permissions set in [`fmode`](#fmode).

The execution of this command requires running with root level privileges, or the tool will report an error.

### touch

**Compile flag**: `-DUSE_CMD_TOUCH`

**Usage**: `touch [file1 [file2 ...]]`

For each argument, if it does not exist, it is created.  If the argument exists and is not a file, then the command fails.  **Warning:** Unlike the standard `touch` command, this will not update the modified time of the file.

If this creates a file, the file will have the file permissions set in [`fmode`](#fmode).

### trunc

**Compile flag**: `-DUSE_CMD_TRUNC`

**Usage**: `trunc [file1 [file2 ...]]`

For each argument, sets the file length to 0 if the file exists, otherwise creates the file.  This is nearly identical to [touch](#touch), with the addition of setting file lengths to 0.

If this creates a file, the file will have the file permissions set in [`fmode`](#fmode).

### dup-r, dup-w, dup-a

**Compile flag**: `-DUSE_CMD_DUP_W` and `-DUSE_CMD_DUP_R` and `-DUSE_CMD_DUP_A`

**Usage**: `dup-w (fd) (file)`

**Usage**: `dup-r (fd) (file)`

**Usage**: `dup-a (fd) (file)`

Opens the given file in either write + truncate mode (`dup-w`), write + append mode (`dup-a`), or read mode (`dup-r`), then duplicates that file descriptor to the "fd" argument.  This duplication remains in effect for the remainder of the execution, or until another `dup` command runs for the same file descriptor.

This is the equivalent of running a command like `echo > out.txt` to redirect stdout, stderr, or stdin to a file.

You can also use the special files "&1" and "&2" to redirect stdout or stderr, respectively, to the file descriptor.  See examples for interesting usages.

If this creates a file, the file will have the file permissions set in [`fmode`](#fmode).

Note that this cannot be used for redirecting output from one command into another; that requires FIFO queues and job control, which this shell doesn't support.

**Example 1:**

Run `echo` with output sent to the file `here.txt`, appending existing text.

```bash
echo -n "foo" > here.txt
presh -c "dup-a 1 here.txt && echo ' bar text' && echo more text"
```

And the file `here.txt` will contain:

```
foo bar text
more
text
```

**Example 2:**

Run `echo` with output sent to stderr

```bash
# These are equivalent
presh -c "dup-w 1 &2 && echo hello"
bash -c "echo hello 1>&2"
```

**Example 3:**

Run `find` command with stdout redirected to file `out.txt` and stderr redirected to file `err.txt`

```bash
# These are equivalent
presh -c "dup-w 1 out.txt && dup-w 2 err.txt && exec /usr/sbin/find /var -type f"
bash -c "find /var -type f >out.txt 2>err.txt"
```

**Example 4:**

Generate some text to a file named `contents.txt`, then and sort it into another file named `sorted.txt`.

```bash
presh -c "dup-w 1 contents.txt \
    && echo foo bar baz \
    && dup-w 1 sorted.txt \
    && dup-r 0 contents.txt \
    && exec /usr/sbin/sort"
```

### export

**Compile flag**: `-DUSE_CMD_EXPORT`

**Usage**: `export (ENV_NAME) (env value)`

Export an environment variable + value into the running process and to-be-run child processes.


### signal-wait

**Compile flag**: `-DUSE_CMD_SIGNAL`

**Usage**: `signal [signal1 [signal2]] [wait]`

Waits for any of the OS signal number arguments before continuing.  If no signal is given (just `signal wait`), then it waits for a standard OS interruption, which will kill the whole process.

Of note, once a signal is added to the list, it is registered for standard OS ignoring.  Only by adding the statement `wait` will the processing wait for the signal to be raised.  This can be used for interesting applications, such as:

```bash
presh -c "signal 2 ; signal 15 wait"
```

This will cause the shell to ignore SIGINT (2, usually sent by a ctrl-c input), and wait for SIGTERM (15).

*Note that `dietlibc` does not support ignoring signals not waited on, and will exit with an error if the to-be-ignored signals are received.*

### exec

**Compile flag**: `-DUSE_CMD_TRUNC`

**Usage**: `exec (quoted command to run)`

Parses the first argument using the [presh quoting rules](#command-parsing) and transfers execution to the command.  The first value extracted is the full path to the executable to run, and the rest of the values are passed as arguments.  If the executable exists and is executable, then presh will not run any more commands.

Commands must be given in the full path; it doesn't look at any environment variable like `PATH`, even with the [environment variable parsing](#environment-variables) enabled.

If the command file does not exist or is not executable, then the next argument will be tried to run.  If none of them can be run, then the `exec` command generates an error.  Note that if the called command can run but generates an error, presh doesn't have control at that point and will not run anything else.

Because of how `exec` works, trailing the command with [`&&`](#chaining-commands) will never cause the following command to run.  This is because the only way `exec` will allow `presh` to run the next command is if it encountered an error attempting to launch the new process.

**Example 1:**

Report the date and time to a file, where the date time tool may be located in several locations, not known ahead of time.  This uses [`dup-w`](#dup-r-dup-w-dup-a) to cause the stdout from the executed command to be sent to the `/etc/time.txt` file, and if no date program is found, the message "unknown date" is written instead.

```bash
presh -c "dup-w 1 /etc/time.txt && exec [/bin/date] [/usr/bin/date] [/sbin/date] ; echo [unknown date]"
```

**Example 2:**

Runs the native copy command to copy files with spaces in their names.  This shows how the embedded quoting makes it much easier to read.

```bash
presh -c "exec [/usr/bin/cp [source file.txt] [target file.txt]]"
```

### spawn

**Compile flag**: `-DUSE_CMD_SPAWN`

**Usage**: `spawn (quoted command) [env for pid]`

Launch a new process in the background.  If the second argument is given, then the launched PID is stored in that value and exported to the environment variables.

**Example 1:**

Launch one command in the background and switch to a different command in the foreground.

```bash
presh -c "\
  spawn [/usr/bin/httpd -c /etc/local.config] && \
  exec [/usr/bin/tail -F /var/log/httpd/error.log]"
```

**Example 2:**

With [environment variable parsing](#environment-variables) enabled, commands can spawn, wait for spawned processes to finish, and kill them.

```bash
presh -c "\
    spawn [/usr/bin/sleep 10000] FOREVER && \
    spawn [/usr/bin/sleep 10] TEN && \
    spawn [/usr/bin/sleep 3] THREE &&\
    echo [Spawned \${FOREVER} then \${TEN} then \${THREE}] ; \
    wait-pid >FIRST ; \
    echo [\${FIRST} just completed.] ;
    wait-pid >SECOND ; \
    echo [\${SECOND} just completed.] ;
    kill-pid 15 \${FOREVER}"
```

### wait-pid

**Compile flag**: `-DUSE_CMD_WAIT_PID`

**Usage**: `wait-pid (pid number) [*(env name)]`

**Usage**: `wait-pid >(env name)`

**Usage**: `wait-pid >(env name) [*(env name)]`

If passed with a numeric argument, it waits for the PID with that number to finish running.  If passed with an argument that starts with `>`, then the command waits for the next child to finish, and stores its PID in the environment variable with the name after the `>`.

Multiple PID or `>ENV` arguments can be given, and the command will wait for each one to complete.  If a follow up argument in the form `*(ENV NAME)` is given, then the exit code from the process is stored in the given environment variable.

**Example 1:**

wait-pid + spawn + exit can be used together to create the equivalent of a normal shell's command execution.

In this example, because the environment variables REQUEST_PID and REQUEST_EXIT might have a chance of being already set, the variable replacement is escaped with an extra `$` in order to prevent the outer string parsing from replacing the value early.

```bash
presh -c "\
  ?: \
    [spawn [/usr/bin/process-request] REQUEST_PID] \
    [ \
      wait-pid \$\${REQUEST_PID} *REQUEST_EXIT && \
      exit \$\${REQUEST_EXIT}
    ] \
    [exit 1] \
  "
```

### kill-pid

**Compile flag**: `-DUSE_CMD_KILL_PID`

**Usage**: `kill-pid (signal) [pid 1 [pid 2 ...]]`

Sends the signal number in the first argument to the processes in the following arguments.

### Chaining Commands

Like most shells, you can chain commands together with `&&` and `;`.  `&&` stops the execution if the previous command failed and allows another command after it; and `;` resets the error count to 0 and allows another command to follow it.  If a new line is encountered, that acts like a `;`.  The common shell `||` chain (run if non-zero error code) is not supported.

A [future feature](https://github.com/groboclown/precision-shell/issues/14) may allow changing the newline behavior via a compile flag.

```bash
$ ls
presh
$ ./presh -c "echo abc && rmdir does-not-exist ; echo dce"
abc
ERROR rmdir: does-not-exist
dce
$ ./presh -c "echo abc && rmdir does-not-exist && echo dce"
abc
ERROR rmdir: does-not-exist
FAIL &&
$ ./presh -c "echo abc \
echo def"
abc
def
```

### Environment Variables

**Compile flag**: `-DUSE_ENVIROMENT_INPUT`

With environment variable parsing enabled, argument parsing will replace text in the form `${VALUE}` with the environment variable contained in the `${}` marks.  Currently, these are not expanded into multiple arguments, but instead will be considered part of a single argument.  Because the [`echo`](#echo) command outputs one argument per line, this shows the behavior clearly:

```bash
$ echo "echo \${ABC} \${ABC}" > script.txt
$ cat script.txt
echo ${ABC} ${ABC}
$ export ABC="a b c"
$ ./presh -f script.txt
a b c
a b c
```

### Standard Script Flag

The tool also supports invoking it with the arguments `-c "commands"` to simulate running the second argument as a script.

### Command Parsing

The parsing is kept simple, and follows these rules:

* A space character (` `), tab, and linefeed (`\r`) separates arguments.
* The parser will handle newlines (`\n`) differently depending on whether you use an input-enabled build or not.  With an input-enabled build, newlines are treated like inserting a `;` between commands, whereas a non-input-enabled build treats newlines like a space.
* Pairs of quote characters (`"` and `'`) can encapsulate text, allowing space characters and other quote characters to be part of an argument, rather than separating arguments.
* Characters can be escaped by adding a backslash (`\`) character.  `\n` turns into a newline, `\r` into a linefeed, `\t` into a tab, and anything else is the character itself.  This is how quote characters can be added, as well as an alternate to adding a space to an argument.

### Script Files

**Compile flag**: `-DUSE_STREAMING_INPUT`

If you use the input-enabled build, then you can use these additional forms of the command:

* `presh -f script-file.txt`
  runs the commands contained in the file `script-file.txt`
* `presh -`
  reads commands from stdin.

### Better Error Reporting

**Compile flag**: `-DREQUIRE_FULL_CMD`

Some commands, like [`ln-s`](#ln-s), require an exact number of arguments.  Unless this flag is set, using the command with just one argument will not cause a failure.  With this flag, `presh` will generate an error.

### Passing Commands from stdin

**Compile flag**: `-DUSE_STREAMING_INPUT`

If you use the input-enabled build, then you can pass the argument `-` to have the tool read commands from stdin.


## Developing

A guide to the special format for command code is in the [source tree](src/README.md).

To compile the shell, you will need a C compiler that includes a version of the standard C libraries.

To test, run:

```bash
chmod +x tests/*.sh && docker build -f build-(libname).Dockerfile .
```

You can build directly, but some of the tests require root privileges, which are safer to run from within a container.

To build through Docker and capture the built executables:

```bash
mkdir -p out
for libname in glibc musl ; do
    docker build -t local/presh-${libname} -f build-${libname}.Dockerfile .
    container=$( docker create local/presh-${libname} )
    docker cp "${container}:/opt/code/out/presh" out/presh.${libname}
    docker cp "${container}:/opt/code/out/presh-debug" out/presh-debug.${libname}
    docker rm "${container}"
done
```

The build generates combinations of the flags for different executables with various enabled actions.  The `version` command lists which flags the executable has enabled.

To enable different commands in the compiled executable from the Docker build, run the build command like so:

```bash
docker build \
  -t local/presh-${libname} -f build-${libname}.Dockerfile \
  --build-arg COMMANDS="rm rmdir chmod chown"
  .
```

Additionally, for your own purposes, you can build it against the "dietlibc" library.  However, this has special considerations in that it's GPL v2, and [you can't distribute the binary under this program's MIT license](http://www.fefe.de/dietlibc/FAQ.txt).

```bash
docker build -t local/presh-dietlibc -f build-dietlibc.Dockerfile . \
    && ./extract-executables.sh local/presh-dietlibc -o out -s .dietlibc -d
```

To bump the version number, change the [version.txt](version.txt) file.  Version numbers must be in a dewey decimal format MAJOR.MINOR.PATCH (e.g. `1.2.3`).


## Contributing

To contribute to the project, submit a PR or open a bug.  All code submitted must be licensed under the MIT license.

Contributing new commands requires (this list assumes that the change is for a single command contained in one file, but it can be multiple commands in a single file, or multiple files, each with their own command):

1. Read through the [source readme file](src/README.md).  This describes how to add commands, though it's lacking on the details that go into a full change.
2. Add cmd_mount.h.in in the src tree and include it in source control changes.
3. Add the cmd_mount.h file to the src/Makefile header list and include the Makefile in source control changes.
4. Generate the .h file by running make and add that to source control.
5. Include the new USE_CMD_* in the flag list in the Makefile.command-flags file, both in the list of flags, and in the INCLUDE_ALL_COMMANDS list.
6. Add new test scripts in the `tests` directory.  The [test readme file](tests/README.md) offers a brief overview of what goes into a test script.
7. Add documentation in the root [README.md](README.md) file, both in the initial command listing, and the detailed description.


## Releasing

Releases should:

1. Bump the version number in [version.txt](version.txt).
2. Bump the version number in [Dockerfile](Dockerfile).
3. Ensure the builds pass.  These run as part of the GitHub actions.
4. The root [README.md](README.md) file is updated with the latest binary file sizes.  The automated builds include the file sizes.
5. Author a new release in GitHub, with the title & tag set to the new version number.  No binary files are included here, but it auto-generates the source tarball.


## License

Precision Shell is licensed under the [MIT license](LICENSE).

Depending on how you compile the executable, the executable may be under a different license.  For example, compiling with the `dietlibc` library causes the compiled executable to be under GPL 2.0.
