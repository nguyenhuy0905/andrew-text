include(CMakeDependentOption)
# compilation options and features

add_library(adrtxt_compile_options INTERFACE)
# ---- feature ----
target_compile_features(adrtxt_compile_options
  INTERFACE
  cxx_std_${CMAKE_CXX_STANDARD}
)

# ---- warnings ----
cmake_dependent_option(adrtxt_WARNINGS "Whether to use compiler warnings" ON
  "PROJECT_IS_TOP_LEVEL;adrtxt_DEV" OFF)
if(adrtxt_WARNINGS)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang"
      OR
      CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(adrtxt_compile_options
      INTERFACE
      -Wall -Wpedantic -Werror -Wextra -Wconversion -Wshadow -Wunused
      -Wsign-conversion -Wcast-qual -Wformat=2 -Wundef -Wnull-dereference
      -Wimplicit-fallthrough)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(adrtxt_compile_options
      INTERFACE
    /W4 /permissive- /volatile:iso /Zc:inline /Zc:preprocessor /Zc:enumTypes
    /Zc:lambda /Zc:__cplusplus /Zc:externConstexpr /Zc:throwingNew /EHsc)
  endif()
endif()

# ---- sanitizers ----
cmake_dependent_option(adrtxt_ASAN "Whether to link with AddressSanitizer" ON
  "PROJECT_IS_TOP_LEVEL;
  NOT adrtxt_MSAN;
  NOT adrtxt_TSAN;
  NOT CMAKE_CXX_COMPILER_ID STREQUAL MSVC;
  adrtxt_DEV" OFF)
set(sanitizer_list "")
if(adrtxt_ASAN)
  list(APPEND sanitizer_list "address")
endif()
# MSan, TSan and ASan are mutually exclusive
# MSan, TSan and UBSan are clang-and-gnu specific
cmake_dependent_option(adrtxt_MSAN "Whether to link with MemorySanitizer" OFF
  "PROJECT_IS_TOP_LEVEL;
  NOT adrtxt_ASAN;
  NOT adrtxt_TSAN;
  adrtxt_DEV;
  NOT CMAKE_CXX_COMPILER_ID STREQUAL MSVC" OFF)
cmake_dependent_option(adrtxt_TSAN "Whether to link with ThreadSanitizer" OFF
  "PROJECT_IS_TOP_LEVEL;
  NOT adrtxt_ASAN;
  NOT adrtxt_MSAN;
  adrtxt_DEV;
  NOT CMAKE_CXX_COMPILER_ID STREQUAL MSVC" OFF)
cmake_dependent_option(adrtxt_UBSAN "Whether to link with"
  "UndefinedBehaviorSanitizer" ON "PROJECT_IS_TOP_LEVEL;
  adrtxt_DEV;
  NOT CMAKE_CXX_COMPILER_ID STREQUAL MSVC" OFF)
if(adrtxt_MSAN)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang"
      OR
      CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(APPEND sanitizer_list "memory")
  endif()
endif()
if(adrtxt_TSAN)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang"
      OR
      CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(APPEND sanitizer_list "thread")
  endif()
endif()
if(adrtxt_UBSAN)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang"
      OR
      CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(APPEND sanitizer_list "undefined")
  endif()
endif()
if(adrtxt_ASAN OR adrtxt_MSAN OR adrtxt_TSAN OR adrtxt_UBSAN)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang"
      OR
      CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(JOIN sanitizer_list "," sanitizer_opts)
    target_compile_options(adrtxt_compile_options
      INTERFACE
      "-fsanitize=${sanitizer_opts}"
    )
    target_link_options(adrtxt_compile_options
        INTERFACE "-fsanitize=${sanitizer_opts}")
  endif()
endif()

# ---- PCH ----
option(adrtxt_PCH "Whether to build with PCH" OFF)
if(adrtxt_PCH)
  target_precompile_headers(adrtxt_compile_options
    INTERFACE
    # add some more here, if you need!
    <stdio.h> <assert.h> <stddef.h>
  )
endif()

# ---- coverage ----
cmake_dependent_option(adrtxt_COV "Whether to link with coverage" ON
  "PROJECT_IS_TOP_LEVEL;adrtxt_DEV" OFF)
if(adrtxt_COV)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang"
      OR
      CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(adrtxt_compile_options INTERFACE --coverage)
    target_link_options(adrtxt_compile_options INTERFACE --coverage)
    include(cmake/coverage.cmake)
  endif()
endif()
