#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
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

// body_fail should contain a `return` statement. cleanup only runs when
// success_cond is true.
// One way to reduce nesting is extracting body_success into a separate
// function.
#define TRY(init, cleanup, success_cond, body_success, body_fail)              \
    do {                                                                       \
        init;                                                                  \
        if (!(success_cond)) {                                                 \
            body_fail                                                          \
        } else {                                                               \
            body_success cleanup;                                              \
        }                                                                      \
    } while (0)

/**
 * \brief string slice, duh.
 * \warning do NOT modify a `struct StrSlice`.
 * \note prefer using `struct StrSliceIter` to accessing `struct StrSlice`'s
 * members.
 */
struct StrSlice {
    const char *buf;
    size_t len;
};

/**
 * \brief iterator on a `StrSliceIter`.
 */
struct StrSliceIter {
    const char *next;
    size_t len_left;
};

/**
 * \brief create a new `struct StrSlice`
 * \warning `t_p_buf`'s lifetime must be at least equal to the returning
 * `struct StrSlice`'s lifetime.
 * \param[in] t_p_buf string buffer that `struct StrSlice` views.
 */
[[nodiscard]] struct StrSlice str_slice_new(const char *t_p_buf);

/**
 * @warning `t_slice`'s lifetime must be at least equal to the returning
 * `struct StrSlice`'s lifetime.
 *
 * If `t_trim_len` is larger or equal to `t_slice`'s length, return a
 * `struct StrSlice` with `len = 0`.
 */
[[nodiscard]] struct StrSlice str_slice_trim_head(struct StrSlice t_slice,
                                                  size_t t_trim_len);
/**
 * @warning `t_slice`'s lifetime must be at least equal to the returning
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

#ifdef __cplusplus
}
#endif
