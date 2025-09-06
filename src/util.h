#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <string.h>

/**
 * \brief Copium \c{std::string_view}.
 */
struct StrSlice {
    const char *buf;
    size_t len;
};

/**
 * \brief Creates a new \c{StrSlice} from the supplied buffer.
 * \param[in] buf String buffer.
 * \warn Do NOT pass in NULL (nullptr is better, but still, please don't).
 */
struct StrSlice str_slice_new(const char *t_p_buf);

/**
 * \brief Creates a new \sa{StrSlice} that views the range \c{[t_start_idx,
 * t_end_idx)} of the supplied \sa{StrSlice}.
 * \param t_slice The \sa{StrSlice}
 * \param t_start_idx Start index.
 * \param t_end_idx End index.
 *
 * If \c{t_end_idx} is larger than the string length, return one viewing
 * \c{[t_start_idx, t_slice.len)}.
 */
struct StrSlice str_slice_subslice(struct StrSlice t_slice, size_t t_start_idx,
                                   size_t t_end_idx);
int str_slice_cmp(struct StrSlice t_lhs, struct StrSlice t_rhs);
struct StrSliceVec {
    struct StrSlice *buf;
    size_t len;
    size_t cap;
};
struct StrSliceVecOptional {
    struct StrSliceVec val;
    bool has_val;
};
/**
 * Doesn't `has_val` if allocation fails.
 */
struct StrSliceVecOptional str_slice_vec_new(size_t t_start_cap);
bool str_slice_vec_insert(struct StrSliceVec *t_p_slice, size_t t_idx,
                          struct StrSlice t_val);
bool str_slice_vec_append(struct StrSliceVec *t_p_slice, struct StrSlice t_val);
void str_slice_vec_nuke(struct StrSliceVec *t_p_slice);

#ifdef __cplusplus
} // extern "C"
#endif
