
#### Overview

cuda/c++/python mixed programming demo by pybind11.(cuda/c++/python混编示例)

```sh
xxx/pybind11_cuda/src/call_python.cpp  # c++ call python using pybind11
xxx/pybind11_cuda/src/example.cpp      # c++ or cuda build as pythom module using pybind11
xxx/pybind11_cuda/src/example.cu       # cuda code
xxx/pybind11_cuda/src/call_c++.cpp     # c++ code
```

#### Setup environment

```sh
sudo apt-get install gcc g++ make cmake python3 python3-pip
pip install numpy

# 为了调试的时候能从Python跳到C++代码的断点
sudo echo 0| sudo tee /proc/sys/kernel/yama/ptrace_scope
```

#### Build

```sh
# generate python library
pip install Cython
pip install distutils
cd xxx/pybind11_cuda/src/python
python3 setup.py build_ext

# build
cd xxx/pybind11_cuda/
mkdir build && cd build
cmake .. && make -j16
sudo make install
```

#### Test

```sh
# python call c++/cuda
cd pybind11_cuda/
python3 test_add.py # for example.cu

# c++ call python
cd xxx/pybind11_cuda/out/lib
./call_python
```


 
