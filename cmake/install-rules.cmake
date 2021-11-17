if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_INSTALL_INCLUDEDIR include/crc32 CACHE PATH "")
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package crc32)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT crc32_Development
)

install(
    TARGETS crc32_crc32
    EXPORT crc32Targets
    RUNTIME #
    COMPONENT crc32_Runtime
    LIBRARY #
    COMPONENT crc32_Runtime
    NAMELINK_COMPONENT crc32_Development
    ARCHIVE #
    COMPONENT crc32_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    crc32_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(crc32_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${crc32_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT crc32_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${crc32_INSTALL_CMAKEDIR}"
    COMPONENT crc32_Development
)

install(
    EXPORT crc32Targets
    NAMESPACE crc32::
    DESTINATION "${crc32_INSTALL_CMAKEDIR}"
    COMPONENT crc32_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
