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
add_library(call_cuda STATIC ${CMAKE_CURRENT_SOURCE_DIR}/call_cuda.cu)

# c++ lib build
add_library(call_cpp STATIC ${CMAKE_CURRENT_SOURCE_DIR}/call_cpp.cpp)

# set cuda properties
set_target_properties(call_cuda PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_RESOLVE_DEVICE_SYMBOLS ON
)

# c++ pybind11 lib build
pybind11_add_module(example ${CMAKE_CURRENT_SOURCE_DIR}/example.cpp)

# link
link_directories(${CMAKE_CURRENT_BINARY_DIR})   # 暴露库路径
target_link_libraries(example PRIVATE pybind11::module pybind11::embed call_cuda call_cpp)
set_target_properties(example PROPERTIES    PREFIX "${PYTHON_MODULE_PREFIX}"
                                            SUFFIX "${PYTHON_MODULE_EXTENSION}")

# c++ call python
add_executable(call_python ${CMAKE_CURRENT_SOURCE_DIR}/call_python.cpp) 
target_link_libraries(call_python PRIVATE pybind11::embed)                                     

# specify install directories
install(FILES ${PROJECT_SOURCE_DIR}/inc/example.h DESTINATION ${CMAKE_INSTALL_PREFIX}/inc)
install(TARGETS call_cuda LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS call_cpp LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS example LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS call_python DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
# install(FILES ${PROJECT_SOURCE_DIR}/src/python/call_calc.cpython-38-x86_64-linux-gnu.so DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)  # only for linux