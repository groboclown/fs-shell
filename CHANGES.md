## v4.0.0

* [d72dc56](d72dc569173a90cedab6bcb4fae9b534c2798e6c)
    * Switched argument and input parsing to a unified front.  This will allow for commands such as `envsubst` to be more easily implemented.
    * Switched quoting to now be re-entrant.  The quote characters are now starting with '[' and ending with ']'.  This is a non-standard formatting, but allows interesting things like better support of the `exec` command. *This may be '(' and ')' before 4.0 releases.*
* (tbd)
    * Added `spawn` command.  Including this command in the executable forces the environment variable usage to be enabled, but doesn't force environment variable parsing.
    * Added `wait-pid` command.  Including this command in the executable forces the environment variable usage to be enabled, but doesn't force environment variable parsing.
    * Added `kill-pid` command.
    * Added `export` command.  Including this command in the executable forces the environment variable usage to be enabled, but doesn't force environment variable parsing.
    * Altered `exec` to take a single argument, and if that command doesn't exist or isn't executable, tries to run the next argument, and so on.
    * Added `subcmd` now that the quote parse rewriting has made it trivial.
    * Added "conditional" command (`?:`) now that `subcmd` shows how easy it is to write this.
    * Added `cd` command.
    * Added `pwd` command.
    * Modified the noop command to also be called `#` to support comment like structures, and `#!` to allow for running presh scripts natively.


## v3.0.0

* [ba250c4](ba250c452722f32677621eba5157b8c1173d0f34)
    * Merged argument parsing implementations together into one file.  This was a backwards incompatible change around how argument parsing without streaming was done, and so required the major version bump to 3.
* [ab726d9](ab726d9c58ecc09dbe234cc28484422c69a69bc6)
    * Added argument parser error checking (#10).  With this, the argument parsing routine was rewritten which made the compiled version smaller.  This significantly changes how non `-c` argument parsing is handled now, and it may not be supported for v3.0.
    * Fixed a bug with the `exec` command when the exec call out fails.  Before, the error was ignored.  Added a test to cover this (`exec-not-a-command.sh`).
* [162b1f1](162b1f1ec35ce8d8fcf19e8dbe274ad01b7d8bc8)
    * Adjusted tests to allow "-" on each flag to run only if the flag is not enabled.
    * Marked `REQUIRE_FULL_CMD` as a top-level Makefile flag.  Added tests for this flag, and added it to the version flags report and combination builds.
    * Added `ENVIRO_INPUT` as top-level Makefile flag.  Added it to the version flags report and combination builds.
    * Added environment variable parsing when the `ENVIRO_INPUT` flag is set (#11).
* [ea4f744](ea4f74499c235c07ead248230c161d94e252078a)
    * Rebranded `fs-shell` as `precision-shell` (presh).


## v2.0.2

* [0875b25](0875b259cf26427f003a570c96ff3620c3a30104)
    * Fixed an issue with allocating memory.  The type sizes were not 100% accurate, but this only led to allocating more memory than what was actually needed.
    * Fixed an issue with tests not running the version command tests.
    * Updated the `sample.Dockerfile` to show how to fully build the command + copy it into a scratch org from a multi-part Dockerfile.


## v2.0.1

* Fixed an issue with many commands reporting ok status when required arguments are not given.  This increases the file size slightly for the minimal commands, though.  This introduces a new element to the command coding.  This is disabled, but can be enabled by adding the define `REQUIRE_FULL_CMD`; turning this on will cause some tests to fail, as it alters the behavior.
* Altered the make to not require Python to build (issue #4).  If Python is not installed and the headers are not generated, then the build will still fail.
* Added a new test build that checks that each individual command flag can build and passes tests.  This also ensures that, with the flag enabled, the `version` command reports the command enabled (issue #3).
* Changed the automated builds to instead run the build once for each command.  The old combinatorics test still exists, but it's been renamed and will only build on pushes to the `combinatorics-test` branch.  This will likely fail because the test takes over 6 hours.
* Added a build to run glibc on Arch Linux, which produces smaller static binaries than on Ubuntu.
* Fixed a bug in the tests that would cause "rm" only command builds to also run rmdir commands.
* General code infrastructure quality improvements.
* Added a `.dockerignore` file to tighten up the docker file sizes.
* Updated documentation to better match the current version.
* Late update to the changes file to include v2.0.0.


## v2.0.0

* Added `fmode` to set a common value to set the file mode used by mkdir, touch, trunc, the dup commands, and some others.  This introduced a backwards-incompatible difference with mkdir, thus making the version jump.
* Changed how the commands are written, based upon a thorough examination on how different coding styles impact the final file size (see [size-experiments.md](size-experiments.md)).  This was a major change that included a lot of experimentation, so the version bump here is too many change files to mention.


## v1.2.0

* Added new commands:
    * touch
    * trunc
    * dup-r
    * dup-w
    * dup-a
* Added a 'build-inventory.txt' file to the output directory to include all the files created.  This helps with scripts to read the list of files, rather than needing to maintain duplicate lists throught the system.


## v1.1.2

* [0b7fd3b](0b7fd3ba4195ab7430773156fd616c133bcf5a09) - changed values to be integers instead of longs.


## v1.1.1

* [1d24bd5](1d24bd5546140a2439c3b88b6f402928b8a1e473) - bug fixes based on test results from running in glibc and dietlibc.
    * Signal handling works better with dietlibc, but not 100%.  dietlibc uses the older POSIX standard for sigwait() which caused incorrect error checking.  This is improved, but there's still an issue with the interesting scenario for ignoring some signals and not waiting on them.
    * Number format error checking is vastly improved to better detect when something is not a numeric value, or has non-numeric text after a number.  This was causing issues with glibc.
* [1d24bd5](1d24bd5546140a2439c3b88b6f402928b8a1e473) - version command now includes the library that built it.  This is pulled from the `version.txt` file.


## v1.1

* Includes new commands:
    * version
    * mv
    * mkdir
    * sleep
    * exec


## v1.0

* Initial release.
* Includes commands:
    * noop
    * echo
    * rm
    * rmdir
    * chmod
    * chown
    * ln-s
    * ln-h
    * signal .. wait (optional build)
* Includes build examples for libraries glibc, musl, dietlibc.
* Standard testing done on musl.