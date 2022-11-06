cmake_minimum_required(VERSION 3.17)

project(B)

add_library(B 
    b.cpp 
    b.h
    )

target_include_directories(
	B
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
	$<INSTALL_INTERFACE:include>
)

if(TARGET D)
else()
	find_package(D CONFIG REQUIRED)
endif()

target_link_libraries(B PUBLIC D)


include(GNUInstallDirs)
install(
    TARGETS B
    EXPORT B_export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES b.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/B)
install(FILES B-config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/B)

install(
    EXPORT B_export
    FILE B_targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/B
)

