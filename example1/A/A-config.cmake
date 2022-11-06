include(CMakeFindDependencyMacro)

find_dependency(B)
find_dependency(C)

include("${CMAKE_CURRENT_LIST_DIR}/A_targets.cmake")