#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
#include <span>
#include <string_view>
extern "C" {
#endif

/**
 * \file util.h
 * \brief Generic utilities
 */

// Some resource cleansing mechanism you can pick and choose from

// cleanup and body can be blocks. init, technically can be block, but that's
// kind of useless.
// However, init can contain many statements.
#define SCOPE(init, cleanup, body)                                             \
    do {                                                                       \
        init;                                                                  \
        body cleanup;                                                          \
    } while (0)

// a `cleanup:` expected inside the function. The order of cleanup should be
// LIFO to the order of declaration.
#define CLEANUP goto cleanup

/**
 * \brief string slice, duh.
 * \warning do NOT modify a `struct StrSlice`.
 * \note prefer using `struct StrSliceIter` to accessing `struct StrSlice`'s
 * members.
 */
struct StrSlice {
    const char *buf;
    size_t len;

#ifdef __cplusplus
    [[nodiscard]] constexpr auto operator==(const StrSlice &t_other) const
        -> bool {
        return this->len == t_other.len &&
               strncmp(this->buf, t_other.buf, t_other.len) == 0;
    }
    [[nodiscard]] constexpr operator std::string_view() const {
        return {this->buf, this->len};
    }
#endif
};

/**
 * \brief iterator on a `StrSliceIter`.
 */
struct StrSliceIter {
    const char *next;
    size_t len_left;
};

/**
 * \warning `t_p_buf`'s lifetime must be at least equal to the returning
 * `struct StrSlice`'s lifetime.
 */
[[nodiscard]] struct StrSlice str_slice_new(const char *t_p_buf);

/**
 * \warning `t_slice`'s lifetime must be at least equal to the returning
 * `struct StrSlice`'s lifetime.
 *
 * If`` `t_trim_len` is larger or equal to `t_slice`'s length, return a
 * `struct StrSlice` with `len = 0`.
 */
[[nodiscard]] struct StrSlice str_slice_trim_head(struct StrSlice t_slice,
                                                  size_t t_trim_len);
/**
 * \warning `t_slice`'s lifetime must be at least equal to the returning
 * `struct StrSlice`'s lifetime.
 *
 * If `t_trim_len` is larger or equal to `t_slice`'s length, return a
 * `struct StrSlice` with `len = 0`.
 */
[[nodiscard]] struct StrSlice str_slice_trim_tail(struct StrSlice t_slice,
                                                  size_t t_trim_len);

[[nodiscard]] struct StrSliceIter str_slice_iter_new(struct StrSlice t_slice);
[[nodiscard]] bool str_slice_iter_has_next(struct StrSliceIter t_iter);
/**
 * You probably could have guessed already, but please don't pass in a null
 * pointer.
 */
[[nodiscard]] char str_slice_iter_next(struct StrSliceIter *t_p_iter);

struct StrSliceQueue {
    struct StrSlice *buf;
    size_t len;
    size_t cap;

#ifdef __cplusplus
    // NOLINTNEXTLINE(*-identifier-naming)
    constexpr auto operator==(const StrSliceQueue &t_other) const -> bool {
        return this->buf == t_other.buf && this->len == t_other.len &&
               this->cap == t_other.cap;
    }
    constexpr operator std::span<StrSlice>() const {
        return {this->buf, this->len};
    }
#endif
};

[[nodiscard]] struct StrSliceQueue str_slice_queue_new();
void str_slice_queue_nuke(struct StrSliceQueue *t_p_queue,
                          void(t_p_free_fn(void *)));
// we give you the option
[[nodiscard]] struct StrSlice *
str_slice_queue_index(struct StrSliceQueue t_queue, size_t t_idx);
[[nodiscard]] bool str_slice_queue_is_empty(struct StrSliceQueue t_queue);
[[nodiscard]] bool str_slice_queue_push(struct StrSliceQueue *t_p_queue,
                                        struct StrSlice t_new_slice,
                                        void *(t_p_malloc_fn(size_t)),
                                        void(t_p_free_fn(void *)));
struct StrSliceQueuePop {
    struct StrSlice val_or_placeholder;
    bool has_value;
};

[[nodiscard]] struct StrSliceQueuePop
str_slice_queue_pop(struct StrSliceQueue *t_p_queue);

#ifdef __cplusplus
}
#endif
