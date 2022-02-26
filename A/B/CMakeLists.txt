cmake_minimum_required(VERSION 3.17)

project(B)

add_library(B 
    b.cpp 
    b.h
    my_cuda_kernel.cu
    )

target_include_directories(
	B
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
	$<INSTALL_INTERFACE:include>
)

include(FindCUDAToolkit)
if(CUDAToolkit_FOUND)
	message("CUDAToolkit_BIN_DIR: ${CUDAToolkit_BIN_DIR}")
	message("CUDAToolkit_INCLUDE_DIRS: ${CUDAToolkit_INCLUDE_DIRS}")
	message("CUDAToolkit_LIBRARY_DIR: ${CUDAToolkit_LIBRARY_DIR}")
	message("CUDAToolkit_TARGET_DIR: ${CUDAToolkit_TARGET_DIR}")
	message("CUDAToolkit_NVCC_EXECUTABLE: ${CUDAToolkit_NVCC_EXECUTABLE}")

    #target_link_libraries(B PRIVATE CUDA::toolkit)
	enable_language(CUDA)
endif()

if(TARGET D)
else()
	find_package(D CONFIG REQUIRED)
endif()

target_link_libraries(B PUBLIC D)
target_link_libraries(B PRIVATE CUDA::cufft)



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

