#include "util.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

struct StrSlice str_slice_new(const char *t_p_buf) {
    return (struct StrSlice){.buf = t_p_buf, .len = strlen(t_p_buf)};
}

struct StrSlice str_slice_subslice(struct StrSlice t_slice, size_t t_start_idx,
                                   size_t t_end_idx) {
    auto new_len = 0;
    if (t_start_idx < t_slice.len && t_end_idx > t_start_idx) {
        auto actual_end = (t_slice.len >= t_end_idx) ? t_end_idx : t_slice.len;
        new_len = actual_end - t_start_idx;
    }
    return (struct StrSlice){.buf = t_slice.buf + t_start_idx, .len = new_len};
}
