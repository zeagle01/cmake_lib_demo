cmake_minimum_required(VERSION 3.15)

project(C)

add_library(C c.cpp c.h)

target_include_directories(
	C
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
	$<INSTALL_INTERFACE:include>
)


if(TARGET D)
else()
	find_package(D CONFIG REQUIRED)
endif()

target_link_libraries(C PUBLIC D)


include(GNUInstallDirs)
install(
    TARGETS C
    EXPORT C_export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES c.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/C)
install(FILES C-config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/C)

install(
    EXPORT C_export
    FILE C_targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/C
)

