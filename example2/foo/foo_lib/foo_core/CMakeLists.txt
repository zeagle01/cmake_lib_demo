
cmake_minimum_required(VERSION 3.21)

project(foo_core)


add_library(foo_core  SHARED)

target_sources(foo_core
	PRIVATE
	 include/foo_core/foo_core.h 
	 src/foo_core.cpp
)

target_include_directories(foo_core 
	PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/foo_core>
	PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
	PUBLIC
    $<INSTALL_INTERFACE:include>
)


include(GenerateExportHeader)
generate_export_header(foo_core EXPORT_FILE_NAME include/foo_core/foo_core_export.h)

##### install
set_target_properties(foo_core PROPERTIES DEBUG_POSTFIX "d")

include(GNUInstallDirs)
install(
    TARGETS foo_core
    EXPORT foo_core_export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

##public headers
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
## dll export macro
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/foo_core/foo_core_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/foo_core)
##export config file
install(FILES cmake/foo_core-config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/foo_core)
## export targets
install(
    EXPORT foo_core_export
    FILE foo_core_targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/foo_core
)
