cmake_minimum_required(VERSION 3.17)

project(A)
set(USE_B_AS_LIB "OFF" CACHE BOOL "use B as lib")
set(USE_C_AS_LIB "OFF" CACHE BOOL "use C as lib")
set(USE_D_AS_LIB "OFF" CACHE BOOL "use D as lib")

##### D 
if(USE_D_AS_LIB)
	find_package(D CONFIG REQUIRED)
else()
	add_subdirectory(D)
	if(TARGET D)
		message( "found target D!")
	else()
		message(FATAL_ERROR "can not find target D any wary")
	endif()
endif()

##### B 
if(USE_B_AS_LIB)
	find_package(B CONFIG REQUIRED)
else()
	add_subdirectory(B)
	if(TARGET B)
		message( "found target B!")
	else()
		message(FATAL_ERROR "can not find target B any wary")
	endif()
endif()

##### C 
if(USE_C_AS_LIB)
	find_package(C CONFIG REQUIRED)
else()
	add_subdirectory(C)
	if(TARGET C)
		message( "found target C!")
	else()
		message(FATAL_ERROR "can not find target B any wary")
	endif()
endif()



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


target_link_libraries(A PUBLIC B)
target_link_libraries(A PUBLIC C)


include(GenerateExportHeader)
generate_export_header(A EXPORT_FILE_NAME A_export.h)


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
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/A_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/A)

install(
    EXPORT A_export
    FILE A_targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/A
)
