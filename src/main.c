#include "cli.h"
#include "logs.h"
#include <stddef.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    auto parse_ret = parse_args(argc, argv);
    if (!parse_ret.is_successful) {
        // TODO: when finish implementing format for ParseArgsError, print it
        // instead of whatever the hell this is.
        debug_log(ERROR, "Memories broken, the truth goes unspoken\n");
        return UH_OH;
    }
    auto args = parse_ret.retval.args;
    run_cli(args);
    return ALL_WELL;
}
