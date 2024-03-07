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

# cuda lib build
cuda_add_library(examplecu ${CMAKE_CURRENT_SOURCE_DIR}/example.cu)

# c++ pybind11 lib build
pybind11_add_module(example ${CMAKE_CURRENT_SOURCE_DIR}/example.cpp)

# link
target_link_libraries(example PRIVATE examplecu)

# specify install directories
install(TARGETS example LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
