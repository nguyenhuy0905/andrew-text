#include "cli.h"
#include "info.h"
#include "logs.h"
#include "util.h"
#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief option preceded by `--` or `-`
 */
enum CliOpt {
    Help,
    Version,
};

static bool match_arg(struct StrSlice, struct StrSliceSpan);
/**
 * The slice excludes the first dash
 */
static void update_flag(struct CliArg *, struct StrSlice);

/**
 * \brief Self-explanatory.
 * \warn Other functions expecting to accept a `StrSliceVec` from this function
 * must *not* nuke the vector. This function *owns* that vector.
 */
struct ParseArgsRet parse_args(int t_argc, char **t_p_argv) {
    struct CliArg args = {
        .help = false, .version = false, .input_file = {.has_val = false}};
    struct ParseArgsRet ret = {.retval = {.err = ALLOC_ERR}, .is_successful = false};
    if (t_argc == 1) {
        ret.retval.err = NO_ARG;
        goto defer;
    }

    assert(t_argc > 1);
    auto vec_ret = str_slice_vec_new((size_t)(t_argc - 1));
    if (!vec_ret.has_val) {
        debug_log(ERROR, "At %s:%d: array allocation failed, nuking program\n",
                  __FILE__, __LINE__);
        goto defer;
    }

    auto vec = vec_ret.val;
    // convert the raw pointers to strings
    for (char **arg = t_p_argv + 1; arg < t_p_argv + t_argc; ++arg) {
        str_slice_vec_append(&vec, str_slice_new(*arg));
    }

    // compare each string to a set of flags
    for (struct StrSlice *slice = vec.buf; slice < vec.buf + vec.len; ++slice) {
        if (str_slice_cmp(str_slice_subslice(*slice, 0, 1),
                          str_slice_new("-")) == 0) {
            update_flag(&args, *slice);
            continue;
        }
        // assume this is input file
        if (args.input_file.has_val) {
            debug_log(ERROR,
                      "Input file already provided.\n"
                      "\t    Already got input file %s\n"
                      "\t    Got extra argument %s\n",
                      args.input_file.val.buf, slice->buf);
            ret.retval.err = INPUT_FILE_ALREADY_PROVIDED;
            goto defer;
        }
        args.input_file.has_val = true;
        args.input_file.val = *slice;
    }

    ret.retval.args = args;
    ret.is_successful = true;
defer:
    str_slice_vec_nuke(&vec);
    return ret;
}

enum RunCliStatus run_cli(const struct CliArg* t_arg) {
    // help takes precedence over everything else
    if (t_arg->help) {
        // TODO: later on, when we have too many options, refactor this into:
        //   - Each sub-command has its own help section.
        //   - The main `--help` just lists all the available subcommands.
        debug_log(INFO,
                  "Printing help message\n\n"
                  "\tadrtxt - Andrew-Text\n\n"

                  "\tOptions:\n"
                  "\t   --help | -h: Print this help message\n"
                  "\t   --version | -v: Print program version\n\n"

                  "\t" EXE_NAME "  Copyright (C) 2025 Huy Nguyen\n"
                  "\tJust a text editor\n\n"
                  "\tThis program is free software: you can redistribute "
                  "it and/or modify\n"
                  "\tit under the terms of the GNU General Public License "
                  "as published by\n"
                  "\tthe Free Software Foundation, either version 3 of the "
                  "License, or\n"
                  "\t(at your option) any later version.\n");
        return ALL_WELL;
    }
    // then version, also taking precedence over anything else
    if (t_arg->version) {
        debug_log(INFO, EXE_NAME " v" VERSION "\n");
        return ALL_WELL;
    }
    assert(t_arg->input_file.has_val);
    debug_log(INFO, "Editing file %s\n", t_arg->input_file.val.buf);
    return ALL_WELL;
}

static bool match_arg(struct StrSlice t_slice, struct StrSliceSpan t_args) {
    for (struct StrSlice *match = t_args.buf; match < t_args.buf + t_args.len;
         ++match) {
        if (str_slice_cmp(t_slice, *match) == 0) {
            return true;
        }
    }
    return false;
}

static void update_flag(struct CliArg *t_p_args, struct StrSlice t_slice) {
    if (match_arg(t_slice,
                  (struct StrSliceSpan){
                      .buf = (struct StrSlice[]){str_slice_new("-help"),
                                                 str_slice_new("h")},
                      .len = 2})) {
        t_p_args->help = true;
    }
    if (match_arg(t_slice,
                  (struct StrSliceSpan){
                      .buf = (struct StrSlice[]){str_slice_new("-version"),
                                                 str_slice_new("v")},
                      .len = 2})) {
        t_p_args->version = true;
    }
}
