#include "../include/CaberNet/tensor.h"

#include "internals/internal_tensor.hpp"
#include "internals/internal_graph.hpp"
#include "internals/operations/internal_operations.hpp"

namespace net {


std::ostream& operator<<(std::ostream& ostream, const Tensor<float>& tensor) {
    ostream << "[";
    for (auto element : tensor) ostream << element << ", ";
    ostream << "]";
    return ostream;
} 

std::ostream& operator<<(std::ostream& ostream, const Tensor<int>& tensor) {
    ostream << "[";
    for (auto element : tensor) ostream << element << ", ";
    ostream << "]";
    return ostream;
} 

Tensor<float> operator + (const Tensor<float> & first, const Tensor<float> & second) {
    return Tensor<float> (std::make_shared<internal::Addition>( first.internal(), second.internal() ));
}

Tensor<float>  operator * (const Tensor<float> & first, const Tensor<float> & second) {
    return Tensor<float>(std::make_shared<internal::Multiplication>( first.internal(), second.internal() ));
}

Tensor<float>  matmul(const Tensor<float> & first, const Tensor<float> & second) {
    return Tensor<float>(std::make_shared<internal::Matmul>( first.internal(), second.internal() ));
}

} // namespace net