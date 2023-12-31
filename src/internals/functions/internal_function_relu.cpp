#include "../config.h"
#include "../internal_array.hpp"
#include "../internal_tensor.hpp"
#include "internal_functions.hpp"

#if defined(USE_EIGEN_BACKEND)

namespace internal {

ReLU::ReLU(Tensor* input) : Function(input) {
    reshape(input->shape());
}

Tensor* ReLU::forward() {
    this->copy(input()->forward());
    Eigen::Map<Eigen::Array<scalar_type, 1, -1>> result_map(
        this->data(),
        this->size());

    result_map = result_map.cwiseMax(0);
    return this;
}

void ReLU::backward(Tensor* gradient) const {
    if (requires_gradient()) {
        Eigen::Map<const Eigen::Array<scalar_type, 1, -1>> result_map(
            this->data(),
            this->size());

        Eigen::Map<Eigen::Array<scalar_type, 1, -1>> gradient_map(
            gradient->data(),
            gradient->size());

        gradient_map = gradient_map * (result_map > 0).cast<scalar_type>();
        input()->backward(gradient);
    }
}

} // namespace internal

#endif // USE_EIGEN_BACKEND