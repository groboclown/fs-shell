# Planning Board

Here's what's planned for the future of the tool.  Because of the backwards compatibility issues, this will be a major version bump.


## Change Argument Quoting

Issue #12

The argument quoting will change to allow for better embedded arguments.  The current candidate for quoting are the characters `[` (start) and `]` (end).  This becomes more necessary when the sub-command parsing is implemented.


## Sub-Command Support

Issue #13

The special command `(` will cause the shell to enter a sub-command, allowing for propigation of error codes to the outer command.  The special argument `)` will mark the end of a command, only if it is not quoted.  Due to this, argument parsing will need to include marking whether an argument includes quoting or not.


## Command Line Arguments

Historically, arguments were used as-is, assuming the calling program already parsed them.  Starting with v3, the parsing algorithm significantly changed to support the much more common use case of "-c" argument parsing.  This raises the question if the old command line parsing should be maintained?  No other major shell supports this execution mode.


## Fix signal-ignore-wait

Issue #18

On musl, this test fails often with 

```
kill: can't kill pid 3110: No such process
Did not stay alive on wait (2).
```
