#include "cli.h"
#include "util.h"

/**
 * @brief option preceded by `--`
 */
enum DoubleDashOpt {
    Help,
    Version,
};

/**
 * @brief argument preceded by `--`
 */
struct DoubleDashArg {
    // `=<something>`. Support for the syntax `--opt=val`
    char *val;
    enum DoubleDashOpt opt;
};

struct CliArg parse_args(int t_argc, char **t_p_argv) {}
