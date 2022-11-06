cmake_minimum_required(VERSION 3.21)

project(foo)


add_executable(foo_test )

target_sources(foo_test 
	PRIVATE 
	main.cpp
)


## link foo_lib
set(USE_FOO_AS_LIB OFF CACHE BOOL "use foo as binary lib")
if(USE_FOO_AS_LIB)
	find_package(foo CONFIG REQUIRED)
else()
	add_subdirectory(foo_lib)
endif()
target_link_libraries(foo_test PRIVATE foo_lib)

## copy dll
add_custom_command(TARGET foo_test POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
  $<TARGET_RUNTIME_DLLS:foo_test> $<TARGET_FILE_DIR:foo_test>
  COMMAND_EXPAND_LISTS
)