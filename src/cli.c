#include "cli.h"
#include "util.h"
#include <stdlib.h>

/**
 * @brief option preceded by `--` or `-`
 */
enum CliOpt {
    Help,
    Version,
};

/**
 * @brief argument preceded by `--` or `-`
 */
struct ArgAst {
    // `=<something>`. Support for the syntax `--opt=val`
    struct StrSlice val;
    enum CliOpt opt;
};

struct CliArg parse_args(int t_argc, char **t_p_argv) {}
