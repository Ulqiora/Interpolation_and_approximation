#include "NewtonPolynomInterp.h"
#include "ResNewtonPol2D.h"
#include <iomanip>
IGraphByDiscrete2D* NewtonPolynomInterp::CreateFunction(const std::vector<double>& X,const std::vector<double>& Y){
    double h = X[1] - X[0];
    SubTable coeff(X.size());
    std::for_each(coeff.begin(), coeff.end(), [&X](std::vector<double>& row) {row.resize(X.size()); });
    coeff[0]=Y;
    for (size_t i = 1; i < X.size(); i++) coeff[i] = CreateColOfSub(coeff[i - 1],i);
    std::cout<<"\n\n";
    for (size_t i = 0 ; i < X.size(); i++) {
        for(size_t j=0;j<X.size();j++){
            std::cout<<coeff[i][j]<<' ';
        }
        std::cout<<'\n';
    }
    return new ResNewtonPol2D(X,Y,h,std::move(coeff),degree_);
}
std::vector<double> NewtonPolynomInterp::CreateColOfSub(const std::vector<double>& col,size_t i) {
    std::vector<double> res(col.size());
    std::transform(col.cbegin(), col.cend() - i, col.cbegin() + 1, res.begin(),
                    [](const double& a, const double& b) { return b-a; });
    return res;
}