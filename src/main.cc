#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "Model/Approximations/LeastSquareApprox/LeastSquareApprox.h"

int main(){
    IGraphing2DByDiscrete* graphing=new LeastSquareApprox(LeastSquareApprox::FuncForLSA::LINEAR);
    std::vector<double> X{1,2,3,4,5,6,7,8,9};
    std::vector<double> Y{2,4,6,8,10,12,14,16,18};
    auto tmp = graphing->CreateFunction(X,Y);
    std::cout<<tmp->calc(1.5);
    std::cout<<3;
    return 0;
}
