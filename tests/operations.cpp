#include "CaberNet.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::ElementsAre;

TEST(operations, matmul) {
    /*
    import torch

    # Initialize tensors
    x = torch.tensor([[1, 2, 3], [4, 5, 6]], dtype=torch.float32, requires_grad=False)
    y = torch.tensor([[1, 1, 1], [-1, -1, -1]], dtype=torch.float32, requires_grad=True)
    z = torch.tensor([[1, 1, 1], [1, 1, 1]], dtype=torch.float32, requires_grad=True)
    I = torch.tensor([[1, 1, 1], [1, 1, 1]], dtype=torch.float32, requires_grad=False)
    w = torch.tensor([[1, 2, 3], [4, 5, 6], [7, 8, 9]], dtype=torch.float32, requires_grad=True)


    # Perform operations

    x = x + I
    x = torch.matmul(x, w)
    x = x * z + y * z + z * y
    x.backward(I)

    # Print results
    print("x : ", x)
    print("Jy: ", y.grad)
    print("Jz: ", z.grad)
    print("Jw: ", w.grad)
    */


    net::Tensor<float> x({2,3}, false); x.fill({1,2,3,4,5,6});
    net::Tensor<float> y({2,3}, true);  y.fill({1,1,1,-1,-1,-1});
    net::Tensor<float> z({2,3}, true);  z.fill(1);  
    net::Tensor<float> I({2,3}, false); I.fill(1);
    net::Tensor<float> w({3,3}, true);  w.fill({1,2,3,4,5,6,7,8,9});

    x = x + I;
    x = net::matmul(x, w);
    x =  x * z + y * z + z * y;
    x.perform();
    x.backward(I);

    /* Results should be:
        x : [44, 53, 62, 76, 94, 112]
        Jy: [2, 2, 2, 2, 2, 2]
        Jz: [44, 53, 62, 76, 94, 112]
        Jw: [7, 7, 7, 9, 9, 9, 11, 11, 11]
    */

    EXPECT_THAT(x, ElementsAre(44, 53, 62, 76, 94, 112));
    EXPECT_THAT(y.gradient(), ElementsAre(2, 2, 2, 2, 2, 2));
    EXPECT_THAT(z.gradient(), ElementsAre(44, 53, 62, 76, 94, 112));
    EXPECT_THAT(w.gradient(), ElementsAre(7, 7, 7, 9, 9, 9, 11, 11, 11));
}

