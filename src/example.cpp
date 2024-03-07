#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "example.h"

namespace py = pybind11;

void add_wrapper(py::array_t<int> a, py::array_t<int> b) {
    auto buf_a = a.request(), buf_b = b.request();
    int *ptr_a = static_cast<int *>(buf_a.ptr);
    int *ptr_b = static_cast<int *>(buf_b.ptr);

    // Call the CUDA function through the header file
    int size = buf_a.size;
    int *c = new int[size];
    add(c, ptr_a, ptr_b, size);

    // Create a new numpy array to return the result
    py::array_t<int> result = py::array_t<int>(size);
    auto buf_result = result.request();
    int *ptr_result = static_cast<int *>(buf_result.ptr);

    // Copy the result from the CUDA function to the numpy array
    for (int i = 0; i < size; i++) {
        ptr_result[i] = c[i];
    }

    delete[] c;
}

PYBIND11_MODULE(example, m) {
    m.def("add", &add_wrapper, "Add two arrays using CUDA");
}
