//adder.hpp
#include <thrust/host_vector.h>
struct Adder {
    thrust::host_vector<float> a_h;
    thrust::host_vector<float> b_h;
    thrust::host_vector<float> r_h;
    int N;

    Adder(int N);
    void set_a(float const * const in);
    void set_b(float const * const in);
    void calc();
    void calc_gpu();
};