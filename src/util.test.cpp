#include "util.h"
#include "test_helper.hpp"
#include <compare>
#include <cstring>
#include <gtest/gtest.h>
#include <string_view>

auto operator<=>(const StrSlice &t_lhs, const StrSlice &t_rhs)
    -> std::strong_ordering {
    int cmp = str_slice_cmp(t_lhs, t_rhs);
    if (cmp == 0) {
        return std::strong_ordering::equal;
    }
    if (cmp > 0) {
        return std::strong_ordering::greater;
    }
    return std::strong_ordering::less;
}
auto operator==(const StrSlice &t_lhs, const StrSlice &t_rhs) -> bool {
    return (t_lhs <=> t_rhs) == std::strong_ordering::equal;
}

namespace test {
// NOTE
// Since GoogleTest requires some operator overloading, the following code is
// not how you would use the util.h header, because we're writing for C.
//
// For example, instead of just `str_slice_1 == str_slice_2`, you must use
// `str_slice_cmp(str_slice_1, str_slice_2) == 0`.
//
// So, why are we testing in C++?
// You might notice this nice class called `helper::Cleanup` we have (which is
// actually `test::helper::Cleanup`). It abuses RAII, which is helpful when
// the `EXPECT`s fails.

// for ""sv
using namespace std::literals;

TEST(StrSlice, Init) {
    auto slice = str_slice_new("hello, world!");
    EXPECT_EQ(slice.len, std::strlen("hello, world!"));
    auto empty_slice = str_slice_new("");
    EXPECT_EQ(empty_slice.len, 0);
}

TEST(StrSlice, Subslice) {
    // normal
    {
        auto slice = str_slice_new("hello, world!");
        auto subslice = str_slice_subslice(slice, 0, 10);
        EXPECT_EQ((std::string_view{subslice.buf, subslice.len}),
                  "hello, wor"sv);
    }
    // beginning index too far off
    {
        auto slice = str_slice_new("hello, world!");
        auto subslice = str_slice_subslice(slice, 69, 71);
        EXPECT_EQ(subslice.len, 0);
        EXPECT_EQ((std::string_view{subslice.buf, subslice.len}), ""sv);
    }
    // ending index too far off
    {
        auto slice = str_slice_new("hello, world!");
        auto subslice = str_slice_subslice(slice, 0, 69);
        EXPECT_EQ(subslice.len, slice.len);
        EXPECT_EQ((std::string_view{subslice.buf, subslice.len}),
                  "hello, world!"sv);
    }
    // ending index is smaller than beginning index
    {
        auto slice = str_slice_new("hello, world!");
        auto subslice = str_slice_subslice(slice, 1, 0);
        EXPECT_EQ(subslice.len, 0);
        EXPECT_EQ((std::string_view{subslice.buf, subslice.len}), ""sv);
    }
    // ending index is equal to beginning index
    {
        auto slice = str_slice_new("hello, world!");
        auto subslice = str_slice_subslice(slice, 1, 1);
        EXPECT_EQ(subslice.len, 0);
        EXPECT_EQ((std::string_view{subslice.buf, subslice.len}), ""sv);
    }
}

TEST(StrSliceVec, Init) {
    auto vec_ret = str_slice_vec_new(4);
    if (vec_ret.has_val) {
        auto vec = vec_ret.val;
        helper::Cleanup c{[&]() { str_slice_vec_nuke(&vec); }};
        EXPECT_EQ(vec.cap, 4);
        EXPECT_EQ(vec.len, 0);
    }
}

TEST(StrSliceVec, Insert) {
    auto vec_ret = str_slice_vec_new(4);
    if (vec_ret.has_val) {
        auto vec = vec_ret.val;
        helper::Cleanup c{[&]() { str_slice_vec_nuke(&vec); }};
        EXPECT_TRUE(
            str_slice_vec_insert(&vec, 0, str_slice_new("hello, world")));
        EXPECT_EQ(vec.len, 1);
        EXPECT_EQ(vec.cap, 4);
        EXPECT_EQ(vec.buf[0], str_slice_new("hello, world"));
        EXPECT_GT(vec.buf[0], str_slice_new("a"));

        EXPECT_TRUE(str_slice_vec_append(&vec, str_slice_new("hallo, welt")));
        EXPECT_EQ(vec.len, 2);
        EXPECT_EQ(vec.cap, 4);
        EXPECT_EQ(vec.buf[1], str_slice_new("hallo, welt"));

        EXPECT_TRUE(str_slice_vec_append(&vec, str_slice_new("random")));
        EXPECT_TRUE(str_slice_vec_append(&vec, str_slice_new("string")));
        EXPECT_TRUE(
            str_slice_vec_append(&vec, str_slice_new("to trigger resize")));
        EXPECT_EQ(vec.len, 5);
        EXPECT_EQ(vec.cap, 8);

        EXPECT_EQ(vec.buf[4], str_slice_new("to trigger resize"));
    }
}

} // namespace test
