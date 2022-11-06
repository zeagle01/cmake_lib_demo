cmake_minimum_required(VERSION 3.21)

project(foo )


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


## install (for packaging)
include(GNUInstallDirs)
install(
    TARGETS foo_test
    EXPORT foo_lib_export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
## install related dll
install(FILES $<TARGET_RUNTIME_DLLS:foo_test> DESTINATION ${CMAKE_INSTALL_BINDIR}/)

## packaging
#set(CPACK_PACKAGE_VENDOR "zeagle")
#set(CPACK_PACKAGE_CONTACT "email@example.com")
#set(CPACK_PACKAGE_DESCRIPTION "foo demo")
set(CPACK_GENERATOR "ZIP")
include(CPack)