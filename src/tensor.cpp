#include "../include/tensor.h"

#include "internals/internal_tensor.hpp"
#include "internals/internal_graph.hpp"
#include "internals/operations/internal_operations.hpp"

namespace net {

Tensor::Tensor(std::shared_ptr<internal::Tensor> tensor) {
    tensor_ = tensor;
    internal::Graph::add(tensor_);
}

Tensor::Tensor(shape_type shape, bool gradient_requirement ) {
    tensor_ = std::make_shared<internal::Tensor>(shape);
    tensor_-> requires_gradient(gradient_requirement);
    internal::Graph::add(tensor_);
}

Tensor::Tensor(shape_type shape, storage_type data, bool gradient_requirement ) {
    tensor_ = std::make_shared<internal::Tensor>(shape);
    std::copy(data.begin(), data.end(), tensor_->begin());
    tensor_-> requires_gradient(gradient_requirement);
    internal::Graph::add(tensor_);
}

internal::Tensor* Tensor::internal() const {return tensor_.get(); }
internal::Tensor* Tensor::internal() { return tensor_.get(); }

void Tensor::backward(const Tensor& gradient) {
    tensor_-> backward(gradient.internal());
}

void Tensor::perform() {
    tensor_-> forward();    
}

Tensor::iterator Tensor::begin() { return tensor_->begin(); }
Tensor::iterator Tensor::end() { return tensor_->end(); }
Tensor::const_iterator Tensor::begin() const { return tensor_->begin(); }
Tensor::const_iterator Tensor::end() const { return tensor_->end(); }
Tensor::const_iterator Tensor::cbegin() const { return tensor_->cbegin(); }
Tensor::const_iterator Tensor::cend() const { return tensor_->cend(); }

Tensor operator + (const Tensor& first, const Tensor& second) {
    return Tensor(std::make_shared<internal::Addition>( first.internal(), second.internal() ));
}

Tensor operator * (const Tensor& first, const Tensor& second) {
    return Tensor(std::make_shared<internal::Multiplication>( first.internal(), second.internal() ));
}

Tensor matmul(const Tensor& first, const Tensor& second) {
    return Tensor(std::make_shared<internal::Matmul>( first.internal(), second.internal() ));
}

} // namespace net

