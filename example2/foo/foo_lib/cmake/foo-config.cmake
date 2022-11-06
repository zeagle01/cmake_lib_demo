
include(CMakeFindDependencyMacro)

find_dependency(foo_core)

include("${CMAKE_CURRENT_LIST_DIR}/foo_targets.cmake")
