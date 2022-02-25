cmake_minimum_required(VERSION 3.15)

project(A)

add_subdirectory(B)
add_subdirectory(C)
add_subdirectory(D)

add_library(A SHARED a.cpp a.h)

target_include_directories(
	A
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../>
	$<INSTALL_INTERFACE:include>
)

target_compile_definitions(A PRIVATE IS_A)


target_link_libraries(A PUBLIC B)
target_link_libraries(A PUBLIC C)


include(GenerateExportHeader)
generate_export_header(A)


include(GNUInstallDirs)
install(
    TARGETS A
    EXPORT A_export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES a.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/A)
install(FILES A-config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/A)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/a_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/A)

install(
    EXPORT A_export
    FILE A_targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/A
)
