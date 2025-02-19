/**
 * @file lib.hpp
 * @brief Some gibberish declarations
 */

#pragma once

namespace lib {
/**
 * @brief Returns true.
 *
 * This function returns The Truth.
 */
auto return_true() -> bool;

class TestClass {
  static const int NUM = 1;

protected:
  int m_num;
};
} // namespace lib
