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
struct ArgAst {};

struct CliArg parse_args(int t_argc, char **t_p_argv) {
    struct CliArg default_args = {.help = false, .version = false};
    return default_args;
}
