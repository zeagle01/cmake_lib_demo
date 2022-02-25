cmake_minimum_required(VERSION 3.15)

project(hello)

set(USE_A_AS_LIB "OFF" CACHE BOOL "use A as lib")

if(TARGET A)
	message(" target A exsit")
else()
	if(USE_A_AS_LIB)
		find_package(A CONFIG REQUIRED)
	else()
		add_subdirectory(A)
	endif()
endif()

add_executable(testA testA.cpp)
target_link_libraries(testA PRIVATE A)

if(MSVC)
	set_property(TARGET testA PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:testA>)
endif()

add_custom_command(
	TARGET testA POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_LIST_DIR}/test_data $<TARGET_FILE_DIR:testA>/test_data
) 

add_custom_command(
	TARGET testA POST_BUILD COMMAND ${CMAKE_COMMAND} -E echo
	"-- copy ${CMAKE_CURRENT_LIST_DIR}/test_data -> $<TARGET_FILE_DIR:testA>/test_data "
) 

add_custom_command(
	TARGET testA POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:A> $<TARGET_FILE_DIR:testA>
) 

add_custom_command(
	TARGET testA POST_BUILD COMMAND ${CMAKE_COMMAND} -E echo
	"-- copy $<TARGET_FILE:A> -> $<TARGET_FILE_DIR:testA> "
) 

