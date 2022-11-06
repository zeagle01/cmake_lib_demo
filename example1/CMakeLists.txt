cmake_minimum_required(VERSION 3.17)

project(cmake_demo)

set(USE_A_AS_LIB "OFF" CACHE BOOL "use A as lib")

if(USE_A_AS_LIB)
	find_package(A CONFIG REQUIRED)
else()
	add_subdirectory(A)
	if(TARGET A)
		message( "found target A!")
	else()
		message(FATAL_ERROR "can not find target A any wary")
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



install(TARGETS testA  RUNTIME DESTINATION test_out)

install(FILES $<TARGET_PDB_FILE:testA> DESTINATION test_out)

#install(FILES $<TARGET_PDB_FILE:A> DESTINATION test_out)# install A's pdb doesn't works
install(FILES $<TARGET_FILE:A> DESTINATION test_out)# install A's dll 'work
