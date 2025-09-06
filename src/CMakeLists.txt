# ---- library definition ----

find_package(PkgConfig)
pkg_check_modules(RAYLIB REQUIRED raylib)
configure_file(info.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/info.h" @ONLY)
target_include_directories(adrtxt_compile_options INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)

target_sources(adrtxt
  PRIVATE
  main.c
)
target_link_libraries(adrtxt
  PRIVATE
  adrtxt_compile_options
  adrtxt_no_main
)

add_library(adrtxt_no_main OBJECT)
target_sources(adrtxt_no_main
  PUBLIC FILE_SET HEADERS FILES
  cli.h
  util.h
  logs.h
  renderer.h
  PRIVATE
  cli.c
  util.c
  logs.c
  renderer.c
)
target_link_libraries(adrtxt_no_main PRIVATE
  adrtxt_compile_options
  ${RAYLIB_LIBRARIES}
  m
)

# endif()

# ---- testing ----

if(BUILD_TESTING)
  find_package(GTest REQUIRED)
  include(GoogleTest)
  add_executable(adrtxt_lib_test)
  target_sources(adrtxt_lib_test
    PRIVATE
    test_helper.hpp
    cli.test.cpp
    util.test.cpp
  )
  target_link_libraries(adrtxt_lib_test
    PRIVATE
    adrtxt_no_main
    adrtxt_compile_options
    GTest::gtest_main
  )
  target_precompile_headers(adrtxt_lib_test
    PRIVATE
    <gtest/gtest.h>
  )
  gtest_discover_tests(adrtxt_lib_test)
endif()
