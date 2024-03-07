# 指定CMake编译最低要求版本
cmake_minimum_required(VERSION 2.8...3.5)

# include .h
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc)
include_directories(${pybind11_INCLUDE_DIR})
include_directories(${CUDA_INCLUDE_DIR})

# # pybind11 lib build
# pybind11_add_module(gpu_library ${CMAKE_CURRENT_SOURCE_DIR}/gpu_library.cu) 

# # specify install directories
# install(TARGETS gpu_library LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

#===========================================================================

# if(CUDA_ENABLE)
#     enable_language(CUDA)
# endif()
# # cuda lib build
# add_library(cudaMatMul cudaMatMul.cu cudaMatMul.h)
# # compile cuda lib to c++ lib
# target_compile_features(cudaMatMul PUBLIC cxx_std_11)
# # c++ executable
# add_executable(main main.cpp)
# # link c++ lib
# target_link_libraries(main cudaMatMul)

# cuda lib build
cuda_add_library(examplecu ${CMAKE_CURRENT_SOURCE_DIR}/example.cu)

# c++ pybind11 lib build
pybind11_add_module(example ${CMAKE_CURRENT_SOURCE_DIR}/example.cpp)

# link
target_link_libraries(example PRIVATE examplecu)
target_link_libraries(example PRIVATE pybind11::module pybind11::embed)
set_target_properties(example PROPERTIES    PREFIX "${PYTHON_MODULE_PREFIX}"
                                            SUFFIX "${PYTHON_MODULE_EXTENSION}")

# specify install directories
install(TARGETS example LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
