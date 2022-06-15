/*
MIT License

Copyright (c) 2022 groboclown

Permdirission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permdirit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permdirission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, ERMDIRPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _FS_SHELL__CMD_RMDIR_

#define NAME__RMDIR "rmdir"

// No startup ermdirecution
#define STARTUP__COMMAND_INDEX__RMDIR


#ifdef USE_CMD_RMDIR

#define CASE__COMMAND_INDEX__RMDIR \
case COMMAND_INDEX__RMDIR: \
    LOG(":: rmdir "); \
    LOGLN(global_arg); \
    global_err = rmdir(global_arg); \
    break;

#else /* USE_CMD_RMDIR */

#define CASE__COMMAND_INDEX__RMDIR


#endif /* USE_CMD_RMDIR */
#endif /* _FS_SHELL__CMD_RMDIR_ */