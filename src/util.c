#include "util.h"
#include <assert.h>
#include <string.h>

struct StrSlice str_slice_new(const char *t_p_buf) {
    return (struct StrSlice){.buf = t_p_buf, .len = strlen(t_p_buf)};
}
struct StrSlice str_slice_trim_tail(struct StrSlice t_slice,
                                    size_t t_trim_len) {
    size_t new_len = t_slice.len;
    if (new_len <= t_trim_len) {
        new_len = 0;
    } else {
        new_len -= t_trim_len;
    }

    return (struct StrSlice){.buf = t_slice.buf, .len = new_len};
}
struct StrSlice str_slice_trim_head(struct StrSlice t_slice,
                                    size_t t_trim_len) {
    size_t new_len = t_slice.len;
    if (new_len <= t_trim_len) {
        new_len = 0;
    } else {
        new_len -= t_trim_len;
    }

    return (struct StrSlice){.buf = t_slice.buf + t_trim_len, .len = new_len};
}

struct StrSliceIter str_slice_iter_new(struct StrSlice t_slice) {
    return (struct StrSliceIter){.next = t_slice.buf, .len_left = t_slice.len};
}
bool str_slice_iter_has_next(struct StrSliceIter t_iter) {
    return t_iter.len_left > 0;
}
char str_slice_iter_next(struct StrSliceIter *t_p_iter) {
    assert(t_p_iter != NULL);
    assert(t_p_iter->len_left > 0);

    char ret = *(t_p_iter->next);
    t_p_iter->len_left -= 1;
    t_p_iter->next += 1;
    return ret;
}
