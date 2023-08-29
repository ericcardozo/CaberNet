#include <Cabernet/tensor.h>
#include <Cabernet/functions.h>

/*

x = torch.tensor([
    [1.,1.],
    [1.,1.]
], requires_grad = True)

W = torch.tensor([
    [2.,2.],
    [2.,2.],
    [2.,2.]
], requires_grad = True)

b = torch.tensor([
    [3.,3.,3.]
], requires_grad = True)

result = F.linear(x, W, b)

print(result)
*/

int main() {
    net::Tensor x({2,2}, true, true); for (auto& e : x) e = 1;
    net::Tensor W({3,2}, true, true); for (auto& e : W) e = 2;
    net::Tensor b({1,3}, true, true); for (auto& e : b) e = 3;
    net::Tensor I({2,3}, false, false); for (auto& e : I) e = 1;

    net::Tensor result = net::function::linear(x,W,b);

    result.backward(I);

    x.print_gradient();
    W.print_gradient();
    b.print_gradient();
}