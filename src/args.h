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
#ifndef FS_SHELL_ARGS
#define FS_SHELL_ARGS


/**
 * @brief Details on the argument parsing.
 * 
 */
enum ArgumentDesc {
    // Normal character.  No escaping or quoting of the text.
    ARG_STATE_NORMAL,

    // The argument included either quoted or escaped text.
    ARG_STATE_ESCAPED,

    // Note on the enum: all "argument is fine" is before _END,
    //   and all "stop parsing arguments" is on or after _END.

    // This is the last argument.  The arg may be NULL, may not be.
    //   This is different from a zero-length argument, where the arg value
    //   is not null but the first character is a zero.
    ARG_STATE_END,

    // The parser encountered an error while loading this argument.
    //   The parser already reported the error.
    ARG_STATE_ERR
};

// Configurable argument maximum size.
//   By making this configurable, it means the tool is better
//   able to be sized into memory constrained environments.
//   The "save count" relates to the commands that need to hold on to
//   the memory.
#ifndef PARSED_ARG_SIZE
#define PARSED_ARG_SIZE    1000
#endif
#ifndef PARSED_ARG_SAVE_COUNT
#define PARSED_ARG_SAVE_COUNT    4
#endif
#ifndef MAX_ENVIRONMENT_VARIABLE_COUNT
#define MAX_ENVIRONMENT_VARIABLE_COUNT 127
#endif


/**
 * @brief A parsed argument text and a description about what it was like.
 * 
 * The argument pointer can be saved up to the PARSED_ARG_SAVE_COUNT.  After
 * that many arguments, the previous arguments will no longer point to the
 * original data.
 */
typedef struct {
    const char *arg;
    enum ArgumentDesc state;
} Argument;


/**
 * @brief Parse the shell execution request into tokens.
 * 
 * After calling this and all advanceToken calls, "closeTokenizer()" must be called.
 * 
 * @return 0 if okay, != 0 if problem.
 */
int args_setup_tokenizer(const int src_argc, char *src_argv[], char * src_envp[]);

/**
 * @brief advance to the next token.
 * 
 * "tokenize" must be called first.
 * 
 * @return const char* 
 */
const Argument *args_advance_token();

/**
 * @brief Clean out the tokenizer after using it.
 * 
 * @return int 0 if okay, non-zero if error.
 */
int args_close_tokenizer();

#endif
