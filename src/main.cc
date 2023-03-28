#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "Model/Approximations/LeastSquareApprox/LeastSquareApprox.h"
#include "Model/Interpolation/CubicSplines/CubicSplines.h"
#include "Model/Interpolation/NewtonPolynomInterp/NewtonPolynomInterp.h"

int main(){
    IGraphing2DByDiscrete* graphing=new CubicSplines();
    std::vector<double> X{1,2,4,7};
    std::vector<double> Y{2,3,1,4};
    std::cout<<X.size()<<"  "<<Y.size()<<'\n';
    auto temp=graphing->CreateFunction(X,Y);
    std::cout<<temp->calc(7);
    return 0;
}