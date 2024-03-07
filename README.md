
#### Overview

cuda/c++/python mixed programming demo by pybind11.(cuda/c++/python混编示例)

#### Setup environment

```sh
sudo apt-get install gcc g++ make cmake python3 python3-pip
pip install numpy
```

#### Build

```sh
cd pybind11_cuda/
mkdir build && cd build
cmake .. && make -j16
sudo make install
```

#### Test

```sh
cd pybind11_cuda/
python3 test_add.py # for example.cu
```


 
