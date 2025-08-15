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

struct CliArg parse_args(int t_argc, char **t_p_argv);

#ifdef __cplusplus
}
#endif // __cplusplus
