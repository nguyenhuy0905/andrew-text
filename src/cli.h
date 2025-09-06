#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "util.h"
#include <stdint.h>
/**
 * @brief Command-line arguments
 */
struct CliArg {
    // --help
    bool help;
    // --version
    bool version;
    // [input file]
    struct StrSliceOptional input_file;
};

enum ParseArgsError: uint8_t {
    NO_ARG = 1,
    NO_SUCH_ARG,
    ALLOC_ERR,
    INPUT_FILE_ALREADY_PROVIDED,
};

enum RunCliStatus: int {
    ALL_WELL,
    UH_OH,
};

struct ParseArgsRet {
    union {
        struct CliArg args;
        enum ParseArgsError err;
    } retval;
    bool is_successful;
};

struct ParseArgsRet parse_args(int t_argc, char **t_p_argv);
enum RunCliStatus run_cli(const struct CliArg* t_arg);

#ifdef __cplusplus
}
#endif // __cplusplus
