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

void str_slice_queue_nuke(struct StrSliceQueue *t_p_queue,
                          void(t_p_free_fn(void *))) {
    (*t_p_free_fn)(t_p_queue->buf);
    t_p_queue->buf = NULL;
    t_p_queue->cap = 0;
    t_p_queue->len = 0;
}

struct StrSlice *str_slice_queue_index(struct StrSliceQueue t_queue,
                                       size_t t_idx) {
    if (t_idx > t_queue.len) {
        return nullptr;
    }

    return &t_queue.buf[t_idx];
}

bool str_slice_queue_is_empty(struct StrSliceQueue t_queue) {
    return t_queue.len == 0;
}

struct StrSliceQueue str_slice_queue_new() {
    return (struct StrSliceQueue){.buf = nullptr, .len = 0, .cap = 0};
}

bool str_slice_queue_push(struct StrSliceQueue *t_p_queue,
                          struct StrSlice t_new_slice,
                          void *(t_p_malloc_fn(size_t)),
                          void(t_p_free_fn(void *))) {
    assert(t_p_queue != NULL);

    if (t_p_queue->cap > t_p_queue->len) {
        t_p_queue->buf[t_p_queue->len] = t_new_slice;
        t_p_queue->len += 1;
        return true;
    }

    bool ret = true;
    struct StrSlice *swap_buf = nullptr;
    if (t_p_queue->cap == 0) {
        swap_buf =
            (struct StrSlice *)(*t_p_malloc_fn)(4 * sizeof(struct StrSlice));
        if (swap_buf == NULL) {
            ret = false;
            CLEANUP;
        }
        swap_buf[0] = t_new_slice;
        struct StrSlice *temp_buf = t_p_queue->buf;
        t_p_queue->buf = swap_buf;
        swap_buf = temp_buf;

        t_p_queue->cap = 4;
        t_p_queue->len = 1;
        ret = true;
        CLEANUP;
    }

    swap_buf = (struct StrSlice *)(*t_p_malloc_fn)(2 * t_p_queue->cap *
                                                   sizeof(struct StrSlice));
    if (swap_buf == NULL) {
        ret = false;
        CLEANUP;
    }
    memcpy(swap_buf, t_p_queue->buf, t_p_queue->len * sizeof(struct StrSlice));
    swap_buf[t_p_queue->len] = t_new_slice;
    struct StrSlice *temp_buf = t_p_queue->buf;
    t_p_queue->buf = swap_buf;
    swap_buf = temp_buf;

    t_p_queue->cap *= 2;
    t_p_queue->len += 1;
    ret = true;

cleanup:
    (*t_p_free_fn)(swap_buf);
    return ret;
}

struct StrSliceQueuePop str_slice_queue_pop(struct StrSliceQueue *t_p_queue) {
    if (t_p_queue->len == 0) {
        return (struct StrSliceQueuePop){
            .val_or_placeholder = str_slice_new(""), .has_value = false};
    }
    t_p_queue->len -= 1;
    return (struct StrSliceQueuePop){.val_or_placeholder =
                                         t_p_queue->buf[t_p_queue->len],
                                     .has_value = true};
}
