#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "Model/Approximations/LeastSquareApprox/LeastSquareApprox.h"
#include "Model/Interpolation/CubicSplines/CubicSplines.h"
#include "Model/Interpolation/NewtonPolynomInterp/NewtonPolynomInterp.h"

int main(){
    IGraphing2DByDiscrete* graphing=new LeastSquareApprox(20);
    std::vector<double> X{1,2,3,4,5,6,7,8,9};
    std::vector<double> Y{1,4,9,16,25,36,49,64,81};
    std::cout<<X.size()<<"  "<<Y.size();
    auto temp=graphing->CreateFunction(X,Y);
    // std::cout<<temp->calc(1.5);
    return 0;
}