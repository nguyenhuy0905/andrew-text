#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Command-line arguments
 */
struct CliArg {
    // --help
    bool help;
    // --version
    bool version;
};

enum ParseArgsError {
    NO_SUCH_ARG,
    ALLOC_ERR,
};

enum RunCliStatus {
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
enum RunCliStatus run_cli(struct CliArg t_arg);

#ifdef __cplusplus
}
#endif // __cplusplus
