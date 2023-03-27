#include "NewtonPolynomInterp.h"
#include "ResNewtonPol2D.h"
#include <iomanip>
IGraphByDiscrete2D* NewtonPolynomInterp::CreateFunction(const std::vector<double>& X,const std::vector<double>& Y){
    double h = X[1] - X[0];
    SubTable coeff(X.size());
    std::for_each(coeff.begin(), coeff.end(), [&X](std::vector<double>& row) {row.resize(X.size()); });
    coeff[0]=Y;
    for (size_t i = 1; i < X.size(); i++) coeff[i] = CreateColOfSub(coeff[i - 1],i);
    for(int i=0;i<X.size();i++){
        for(int j=0;j<X.size();j++){
            printf("%9f",coeff[j][i]);
        }
        std::cout<<'\n';
    }
    std::vector<double> firstSubInTable;
    firstSubInTable.reserve(coeff.size());
    std::for_each(coeff.begin(), coeff.end(), [&firstSubInTable](const std::vector<double>& col) {
        firstSubInTable.push_back(col.front());
    });
    return new ResNewtonPol2D({X.front(),X.back()},h,std::move(firstSubInTable));
}
std::vector<double> NewtonPolynomInterp::CreateColOfSub(const std::vector<double>& col,size_t i) {
    std::vector<double> res(col.size());
    std::transform(col.cbegin(), col.cend() - i, col.cbegin() + 1, res.begin(),
                    [](const double& a, const double& b) { return b-a; });
    return res;
}