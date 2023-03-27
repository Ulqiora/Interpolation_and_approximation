#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "Model/Approximations/LeastSquareApprox/LeastSquareApprox.h"
#include "Model/Interpolation/CubicSplines/CubicSplines.h"
#include "Model/Interpolation/NewtonPolynomInterp/NewtonPolynomInterp.h"

int main(){
    IGraphing2DByDiscrete* graphing=new NewtonPolynomInterp();
    std::vector<double> X{1, 3.5, 6, 8.5, 11, 13.5, 16};
    std::vector<double> Y{1.4142,3.3741,4.4375,5.2223,5.862,6.4106,6.8957};
    std::cout<<X.size()<<"  "<<Y.size()<<'\n';
    auto temp=graphing->CreateFunction(X,Y);
    std::cout<<temp->calc(8.5);
    return 0;
}