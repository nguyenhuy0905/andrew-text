if(CMAKE_SKIP_INSTALL_RULES)
  return()
endif()
set(adrtxt_INSTALLS adrtxt adrtxt_no_main adrtxt_compile_options)
include(GNUInstallDirs)
install(TARGETS ${adrtxt_INSTALLS}
  EXPORT adrtxtTargets
  FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/adrtxt
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/adrtxt
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/adrtxt
)
if(EXISTS "${PROJECT_BINARY_DIR}/adrtxt_export.h")
  install(FILES
    ${PROJECT_BINARY_DIR}/adrtxt_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/adrtxt
  )
endif()
install(EXPORT adrtxtTargets
  FILE adrtxtTargets.cmake
  NAMESPACE adrtxt::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/adrtxt
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/adrtxtConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES "${CMAKE_CURRENT_LIST_DIR}/install-config.cmake"
  RENAME "adrtxtConfig.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/adrtxt
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/adrtxtConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/adrtxt)
