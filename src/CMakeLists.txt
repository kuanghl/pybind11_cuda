# 指定CMake编译最低要求版本
cmake_minimum_required(VERSION 2.8...3.5)

# include .h
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc)
include_directories(${pybind11_INCLUDE_DIR})

# # pybind11 lib build
# pybind11_add_module(gpu_library ${CMAKE_CURRENT_SOURCE_DIR}/gpu_library.cu) 

# # specify install directories
# install(TARGETS gpu_library LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

#===========================================================================

# cuda lib build
add_library(addercu STATIC ${CMAKE_CURRENT_SOURCE_DIR}/adder.cu)

# set cuda properties
set_target_properties(addercu PROPERTIES 
    POSITION_INDEPENDENT_CODE ON
    CUDA_VISIBILITY_PRESET "hidden"
    # CUDA_SEPARABLE_COMPILATION ON
)

# c++ lib build
add_library(adder MODULE    ${CMAKE_CURRENT_SOURCE_DIR}/adder.cpp)

# set c++ properties
set_target_properties(adder PROPERTIES 
    CXX_VISIBILITY_PRESET "hidden"
    INTERPROCEDURAL_OPTIMIZATION TRUE
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
)

target_link_libraries(adder PRIVATE addercu)
target_link_libraries(adder PRIVATE pybind11::module)

# specify install directories
install(TARGETS adder LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)