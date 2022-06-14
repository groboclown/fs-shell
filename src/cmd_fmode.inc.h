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

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EFMODEPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _FS_SHELL__CMD_FMODE_

#define NAME__FMODE "fmode"


#ifdef USES_FMODE

#define STARTUP__COMMAND_INDEX__FMODE \
else if (strequal(global_arg, NAME__FMODE)) { \
    global_cmd = COMMAND_INDEX__FMODE; \
}



#define CASE__COMMAND_INDEX__FMODE \
case COMMAND_INDEX__FMODE: \
    LOG(":: fmode "); \
    LOGLN(global_arg); \
    /* File mode is only up to the first 3 nybbles. */ \
    /* Due to error checking, this will not change fmode unless it's okay. */ \
    global_arg1_i = helper_arg_to_uint(global_arg, 8, 0777); \
    if (global_arg1_i < 0) { \
        global_err = 1; \
        break; \
    } \
    global_fmode = global_arg1_i; \
    \
    /* Nothing must run after this. */ \
    global_cmd = COMMAND_INDEX__ERR; \
    break;


#else /* USES_FMODE */
#define CASE__COMMAND_INDEX__FMODE
#define STARTUP__COMMAND_INDEX__FMODE
#endif /* USES_FMODE */

#endif /* _FS_SHELL__CMD_FMODE_ */
