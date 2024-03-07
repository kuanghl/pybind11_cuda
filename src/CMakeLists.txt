# 指定CMake编译最低要求版本
cmake_minimum_required(VERSION 2.8...3.5)

# include .h
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc)
include_directories(${pybind11_INCLUDE_DIR})

# pybind11 lib build
pybind11_add_module(gpu_library ${CMAKE_CURRENT_SOURCE_DIR}/gpu_library.cu) 

# specify install directories
install(TARGETS gpu_library LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

#===========================================================================

##pybind11 sets -fvisibility=hidden in INTERFACE_COMPILE_OPTIONS on it's module target
get_target_property(modifacecopts module INTERFACE_COMPILE_OPTIONS)
list(REMOVE_ITEM modifacecopts "-fvisibility=hidden")
set_target_properties(module PROPERTIES INTERFACE_COMPILE_OPTIONS "${modifacecopts}")

# cuda lib build
add_library(adder MODULE    ${CMAKE_CURRENT_SOURCE_DIR}/adder.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/adder.cu)

# set cuda and c++ properties
set_target_properties(adder PROPERTIES 
    POSITION_INDEPENDENT_CODE ON
    CUDA_VISIBILITY_PRESET "hidden"
    CXX_VISIBILITY_PRESET "hidden"
    INTERPROCEDURAL_OPTIMIZATION TRUE
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
)

target_link_libraries(adder PRIVATE pybind11::module)

# specify install directories
install(TARGETS adder LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)