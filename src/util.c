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

struct StrSliceVecOptional str_slice_vec_new(size_t t_start_cap) {
    struct StrSlice *buf = malloc(sizeof(struct StrSlice) * t_start_cap);
    if (buf == nullptr) {
        return (struct StrSliceVecOptional){.has_val = false};
    }
    return (struct StrSliceVecOptional){
        .val = {.buf = buf, .len = 0, .cap = t_start_cap}, .has_val = true};
}

int str_slice_cmp(struct StrSlice t_lhs, struct StrSlice t_rhs) {
    return strncmp(t_lhs.buf, t_rhs.buf,
                   (t_lhs.len > t_rhs.len) ? t_rhs.len : t_lhs.len);
}

bool str_slice_vec_insert(struct StrSliceVec *t_p_slice, size_t t_idx,
                          struct StrSlice t_val) {
    assert(t_p_slice != nullptr);
    if (t_idx > t_p_slice->len) {
        return false;
    }

    if (t_p_slice->cap == t_p_slice->len) {
        struct StrSlice *new_buf =
            malloc(2 * t_p_slice->cap * sizeof(struct StrSlice));
        if (new_buf == nullptr) {
            return false;
        }
        memcpy(new_buf, t_p_slice->buf,
               t_p_slice->len * sizeof(struct StrSlice));
        free(t_p_slice->buf);
        t_p_slice->buf = new_buf;
        t_p_slice->cap *= 2;
    }

    memmove(t_p_slice->buf + t_idx + 1, t_p_slice->buf + t_idx,
            t_p_slice->len - t_idx);
    t_p_slice->buf[t_idx] = t_val;
    ++t_p_slice->len;
    return true;
}

bool str_slice_vec_append(struct StrSliceVec *t_p_slice,
                          struct StrSlice t_val) {
    assert(t_p_slice != nullptr);
    return str_slice_vec_insert(t_p_slice, t_p_slice->len, t_val);
}

void str_slice_vec_nuke(struct StrSliceVec *t_p_slice) {
    assert(t_p_slice != nullptr);
    free(t_p_slice->buf);
    t_p_slice->len = 0;
    t_p_slice->cap = 0;
}
