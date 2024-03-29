
cmake_minimum_required(VERSION 3.21)

project(foo_app)


add_executable(foo_app main.cpp)

## link foo_lib
find_package(foo CONFIG REQUIRED)
target_link_libraries(foo_app PRIVATE foo_lib)

## copy dll
add_custom_command(TARGET foo_app POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
  $<TARGET_RUNTIME_DLLS:foo_app> $<TARGET_FILE_DIR:foo_app>
  COMMAND_EXPAND_LISTS
)


## packaging
include(GNUInstallDirs)
install(
    TARGETS foo_app
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
## install related dll
#install(FILES $<TARGET_RUNTIME_DLLS:foo_app> DESTINATION ${CMAKE_INSTALL_BINDIR}/)
install( IMPORTED_RUNTIME_ARTIFACTS foo_lib )
install( IMPORTED_RUNTIME_ARTIFACTS foo_core )

## packaging
set(CPACK_GENERATOR "ZIP")
include(CPack)
