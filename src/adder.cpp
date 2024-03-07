#include "adder.hpp"
#include "pybind11/pybind11.h"
#include "pybind11/numpy.h"
#include <stdexcept>

namespace py = pybind11;

void bind_Adder(py::module& m) {
    py::class_<Adder>(m,"Adder","Module docstring")
        .def(py::init<int>(), py::arg("N"), "Init Adder")
        .def(
            "set_a"
            , [](Adder& self, py::array_t<float, py::array::c_style | py::array::forcecast> in) {
                py::buffer_info ai = in.request();
                if (ai.ndim!=1 || ai.shape[0]!=self.N || ai.strides[0]!=sizeof(float)) {
                    throw std::runtime_error("Shape of given numpy array must be (N,)! Type must be float.");
                }
                self.set_a(static_cast<float const * const>(ai.ptr));
            }
            , py::arg("in")
            , "Set a."
        )
        .def(
            "set_b"
            , [](Adder& self, py::array_t<float, py::array::c_style | py::array::forcecast> in) {
                py::buffer_info ai = in.request();
                if (ai.ndim!=1 || ai.shape[0]!=self.N || ai.strides[0]!=sizeof(float))
                    throw std::runtime_error("Shape of given numpy array must be (N,)! Type must be float.");
                self.set_b(static_cast<float const * const>(ai.ptr));
            }
            , py::arg("in")
            , "Set b."
        )
        .def(
            "get_r"
            , [](Adder& self, py::array_t<float> x) {
                auto r = x.mutable_unchecked<1>(); 
                for (ssize_t i = 0; i < r.shape(0); i++) {
                    r(i) = self.r_h[i];
                }
            }
            , py::arg("x").noconvert())
        .def("calc", &Adder::calc, "Calculate on CPU.")
        .def("calc_gpu", &Adder::calc_gpu, "Calculate on GPU.");
}

PYBIND11_MODULE(dummy, m) {
    bind_Adder(m);
}