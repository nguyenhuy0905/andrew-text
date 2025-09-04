#include "util.h"
#include <cstring>
#include <gtest/gtest.h>
#include <string_view>

// for ""sv
using namespace std::literals;

TEST(StrSlice, Init) {
    auto slice = str_slice_new("hello, world!");
    ASSERT_EQ(slice.len, std::strlen("hello, world!"));
    auto empty_slice = str_slice_new("");
    ASSERT_EQ(empty_slice.len, 0);
}

TEST(StrSlice, Subslice) {
    // normal
    {
        auto slice = str_slice_new("hello, world!");
        auto subslice = str_slice_subslice(slice, 0, 10);
        ASSERT_EQ((std::string_view{subslice.buf, subslice.len}),
                  "hello, wor"sv);
    }
    // beginning index too far off
    {
        auto slice = str_slice_new("hello, world!");
        auto subslice = str_slice_subslice(slice, 69, 71);
        ASSERT_EQ(subslice.len, 0);
        ASSERT_EQ((std::string_view{subslice.buf, subslice.len}), ""sv);
    }
    // ending index too far off
    {
        auto slice = str_slice_new("hello, world!");
        auto subslice = str_slice_subslice(slice, 0, 69);
        ASSERT_EQ(subslice.len, slice.len);
        ASSERT_EQ((std::string_view{subslice.buf, subslice.len}),
                  "hello, world!"sv);
    }
    // ending index is smaller than beginning index
    {
        auto slice = str_slice_new("hello, world!");
        auto subslice = str_slice_subslice(slice, 1, 0);
        ASSERT_EQ(subslice.len, 0);
        ASSERT_EQ((std::string_view{subslice.buf, subslice.len}), ""sv);
    }
    // ending index is equal to beginning index
    {
        auto slice = str_slice_new("hello, world!");
        auto subslice = str_slice_subslice(slice, 1, 1);
        ASSERT_EQ(subslice.len, 0);
        ASSERT_EQ((std::string_view{subslice.buf, subslice.len}), ""sv);
    }
}
