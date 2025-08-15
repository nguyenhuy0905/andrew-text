#include "util.h"
#include <array>
#include <cstdlib>
#include <gtest/gtest.h>
#include <string_view>

using namespace std::literals::string_view_literals;

TEST(Util, StrSlice_Init) {
    auto slice = str_slice_new("hello, world\n");
    EXPECT_NE(slice.buf, nullptr);
    EXPECT_EQ(std::string_view(slice.buf, slice.len), "hello, world\n"sv);
}

TEST(Util, StrSlice_Trim) {
    auto slice = str_slice_new("hello, world\n");
    auto trim_head_slice = str_slice_trim_head(slice, 2);
    EXPECT_NE(trim_head_slice.buf, nullptr);
    EXPECT_EQ(std::string_view(trim_head_slice.buf, trim_head_slice.len),
              "llo, world\n"sv);

    auto trim_tail_slice = str_slice_trim_tail(slice, 2);
    EXPECT_NE(trim_tail_slice.buf, nullptr);
    EXPECT_EQ(std::string_view(trim_tail_slice.buf, trim_tail_slice.len),
              "hello, worl"sv);
}

TEST(Util, StrSlice_Iter) {
    auto slice = str_slice_new("hi\n");
    auto iter = str_slice_iter_new(slice);

    EXPECT_TRUE(str_slice_iter_has_next(iter));
    EXPECT_EQ(str_slice_iter_next(&iter), 'h');
    EXPECT_TRUE(str_slice_iter_has_next(iter));
    EXPECT_EQ(str_slice_iter_next(&iter), 'i');
    EXPECT_TRUE(str_slice_iter_has_next(iter));
    EXPECT_EQ(str_slice_iter_next(&iter), '\n');
    EXPECT_FALSE(str_slice_iter_has_next(iter));
}

TEST(Util, StrSliceQueue_Init) {
    auto queue = str_slice_queue_new();
    ASSERT_EQ(queue, (StrSliceQueue{.buf = nullptr, .len = 0, .cap = 0}));
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(Util, StrSliceQueue_Push_Pop) {
    auto queue = str_slice_queue_new();
    ASSERT_TRUE(str_slice_queue_push(&queue, str_slice_new("hello, world\n"),
                                     std::malloc, std::free));
    ASSERT_EQ(queue.cap, 4);
    ASSERT_EQ(queue.len, 1);
    auto *first_item = str_slice_queue_index(queue, 0);
    ASSERT_NE(first_item, nullptr);
    ASSERT_EQ(static_cast<std::string_view>(*first_item), "hello, world\n"sv);

    ASSERT_TRUE(str_slice_queue_push(&queue, str_slice_new("i tried so hard\n"),
                                     std::malloc, std::free));
    ASSERT_TRUE(str_slice_queue_push(&queue, str_slice_new("and got so far\n"),
                                     std::malloc, std::free));
    ASSERT_TRUE(str_slice_queue_push(&queue, str_slice_new("but in the end\n"),
                                     std::malloc, std::free));
    ASSERT_TRUE(str_slice_queue_push(&queue,
                                     str_slice_new("it doesn't even matter\n"),
                                     std::malloc, std::free));
    ASSERT_EQ(queue.cap, 8);
    ASSERT_EQ(queue.len, 5);
    // [[maybe_unused]] auto test_arr = std::array{
    //     StrSlice{.buf = "hello, world\n", .len = sizeof("hello, world\n")
    //     - 1}, StrSlice{.buf = "i tried so hard\n",
    //              .len = sizeof("i tried so hard\n") - 1},
    //     StrSlice{.buf = "and got so far\n",
    //              .len = sizeof("and got so far\n") - 1},
    //     StrSlice{.buf = "but in the end\n",
    //              .len = sizeof("but in the end\n") - 1},
    //     StrSlice{.buf = "it doesn't even matter\n",
    //              .len = sizeof("it doesn't even matter\n") - 1},
    // };
    auto test_arr = std::array{"hello, world\n"sv, "i tried so hard\n"sv,
                               "and got so far\n"sv, "but in the end\n"sv,
                               "it doesn't even matter\n"sv};
    for (size_t idx = 0; idx < test_arr.size(); ++idx) {
        auto *item = str_slice_queue_index(queue, idx);
        ASSERT_NE(item, nullptr);
        ASSERT_EQ(static_cast<std::string_view>(*item), test_arr.at(idx));
    }
    ASSERT_FALSE(str_slice_queue_is_empty(queue));
    auto pop = str_slice_queue_pop(&queue);
    ASSERT_TRUE(pop.has_value);
    ASSERT_EQ(pop.val_or_placeholder, "it doesn't even matter\n"sv);
    pop = str_slice_queue_pop(&queue);
    ASSERT_TRUE(pop.has_value);
    ASSERT_EQ(pop.val_or_placeholder, "but in the end\n"sv);
    pop = str_slice_queue_pop(&queue);
    ASSERT_TRUE(pop.has_value);
    ASSERT_EQ(pop.val_or_placeholder, "and got so far\n"sv);
    pop = str_slice_queue_pop(&queue);
    ASSERT_TRUE(pop.has_value);
    ASSERT_EQ(pop.val_or_placeholder, "i tried so hard\n"sv);
    pop = str_slice_queue_pop(&queue);
    ASSERT_TRUE(pop.has_value);
    ASSERT_EQ(pop.val_or_placeholder, "hello, world\n"sv);
    pop = str_slice_queue_pop(&queue);
    ASSERT_FALSE(pop.has_value);
    ASSERT_TRUE(str_slice_queue_is_empty(queue));

    str_slice_queue_nuke(&queue, std::free);
}
// NOLINTEND(readability-function-cognitive-complexity)
