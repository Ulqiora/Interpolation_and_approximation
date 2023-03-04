#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "Model/Approximations/LeastSquareApprox/LeastSquareApprox.h"

int main(){
    IGraphing2DByDiscrete* graphing=new LeastSquareApprox(3);
    std::vector<double> X{1,2,3};
    std::vector<double> Y{1,2,3};
    auto res = graphing->CreateFunction(X,Y);
    std::cout<<res->calc(100);
    return 0;
}
