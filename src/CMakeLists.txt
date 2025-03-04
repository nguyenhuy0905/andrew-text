# ---- library definition ----

if(adrtxt_MODULE)
  target_sources(adrtxt_lib_module
    PUBLIC
    FILE_SET CXX_MODULES FILES
    lib.cpp
  )
  target_link_libraries(adrtxt_lib_module
    PRIVATE
    adrtxt_compile_options
  )
else()
  target_sources(adrtxt_lib
    PUBLIC
    FILE_SET HEADERS FILES
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/lib.hpp>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/adrtxt/lib.hpp>
    PRIVATE
    lib.cpp
  )
  target_link_libraries(adrtxt_lib
    PRIVATE
    adrtxt_compile_options
  )
endif()

# ---- testing ----

if(BUILD_TESTING)
  include(GoogleTest)
  find_package(GTest REQUIRED)
  add_executable(adrtxt_lib_test)
  target_sources(adrtxt_lib_test
    PRIVATE
    lib.test.cpp
  )
  if(adrtxt_MODULE)
    target_link_libraries(adrtxt_lib_test
      PRIVATE
      adrtxt_lib_module
      adrtxt_compile_options
      GTest::gtest_main
    )
  else()
    target_link_libraries(adrtxt_lib_test
      PRIVATE
      adrtxt_lib
      adrtxt_compile_options
      GTest::gtest_main
    )
  endif()
  target_precompile_headers(adrtxt_lib_test
    PRIVATE
    <gtest/gtest.h>
  )
  gtest_discover_tests(adrtxt_lib_test)
endif()
