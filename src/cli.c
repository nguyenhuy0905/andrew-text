#include "cli.h"
#include "util.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief option preceded by `--` or `-`
 */
enum CliOpt {
    Help,
    Version,
};

/**
 * \brief Self-explanatory
 */
struct ParseArgsRet parse_args(int t_argc, char **t_p_argv) {
    struct CliArg default_args = {.help = false, .version = false};
    // return default_args;
}
