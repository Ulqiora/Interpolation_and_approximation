#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "Model/Approximations/LeastSquareApprox/LeastSquareApprox.h"
#include "Model/Interpolation/CubicSplines/CubicSplines.h"
#include "Model/Interpolation/NewtonPolynomInterp/NewtonPolynomInterp.h"

int main(){
    IGraphing2DByDiscrete* graphing=new NewtonPolynomInterp();
    std::vector<double> X{1,2,3,4};
    std::vector<double> Y{1,4,9,16};
    auto temp=graphing->CreateFunction(X,Y);
    std::cout<<temp->calc(0.5);
    return 0;
}
