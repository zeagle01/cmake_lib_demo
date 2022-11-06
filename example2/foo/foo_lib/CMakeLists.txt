
cmake_minimum_required(VERSION 3.21)

project(foo_lib)


add_library(foo_lib  SHARED)

target_sources(foo_lib
	PRIVATE
	 include/foo/foo.h 
	 src/foo.cpp
)

target_include_directories(foo_lib 
	PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/foo>
	PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
	PUBLIC
    $<INSTALL_INTERFACE:include>
)


include(GenerateExportHeader)
generate_export_header(foo_lib EXPORT_FILE_NAME include/foo/foo_export.h)


## link foo_core
set(USE_FOO_CORE_AS_LIB OFF CACHE BOOL "use foo_core as binary lib")
if(USE_FOO_CORE_AS_LIB)
	find_package(foo_core CONFIG REQUIRED)
else()
	add_subdirectory(foo_core)
endif()
target_link_libraries(foo_lib PRIVATE foo_core)


##### install
set_target_properties(foo_lib PROPERTIES DEBUG_POSTFIX "d")

include(GNUInstallDirs)
install(
    TARGETS foo_lib
    EXPORT foo_lib_export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

##public headers
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
## dll export macro
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/foo/foo_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/foo)
##export config file
install(FILES cmake/foo-config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/foo)
## export targets
install(
    EXPORT foo_lib_export
    FILE foo_targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/foo
)
