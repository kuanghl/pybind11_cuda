//adder.cu
#include "adder.hpp"
#include <thrust/device_vector.h>

Adder::Adder(int N): N(N),a_h(N),b_h(N),r_h(N) {}
void Adder::set_a(float const * const in) {
    for (int i=0; i<N; ++i) {
        a_h[i] = in[i];
    }
}
void Adder::set_b(float const * const in) {
    for (int i=0; i<N; ++i) {
        b_h[i] = in[i];
    }
}
void Adder::calc() {
    for (int i=0; i<N; ++i) {
        r_h[i] = a_h[i]+b_h[i];
    }
}
void Adder::calc_gpu() {
    thrust::device_vector<float> a_d(a_h);
    thrust::device_vector<float> b_d(b_h);
    thrust::device_vector<float> r_d(r_h);

    thrust::transform(a_d.begin(), a_d.end(), b_d.begin(), r_d.begin(),thrust::plus<float>());
    r_h = r_d;
}