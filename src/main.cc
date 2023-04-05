#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "Model/Approximations/LeastSquareApprox/LeastSquareApprox.h"
#include "Model/Interpolation/CubicSplines/CubicSplines.h"
#include "Model/Interpolation/NewtonPolynomInterp/NewtonPolynomInterp.h"

int main(){
    IGraphing2DByDiscrete* graphing=new NewtonPolynomInterp();
    std::vector<double> X{1,3.5,6,8.5,11,13.5,16};
    std::vector<double> Y{1.414214,3.374083,4.437511,5.222273,5.861997,6.410576,6.895694};
    std::cout<<X.size()<<"  "<<Y.size()<<'\n';
    auto temp=graphing->CreateFunction(X,Y);
    std::cout<<temp->calc(11.5)<<'\n';
    std::cout<<log(11.5)+sqrt(1+11.5)<<'\n';
    return 0;
}