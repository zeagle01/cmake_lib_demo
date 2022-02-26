include(CMakeFindDependencyMacro)

find_dependency(D)
include(FindCUDAToolkit)

include("${CMAKE_CURRENT_LIST_DIR}/B_targets.cmake")