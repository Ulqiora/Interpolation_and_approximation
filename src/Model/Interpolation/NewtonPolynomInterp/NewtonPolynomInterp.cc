#include "NewtonPolynomInterp.h"
#include "ResNewtonPol2D.h"

IGraphByDiscrete2D* NewtonPolynomInterp::CreateFunction(const std::vector<double>& X,const std::vector<double>& Y){
    double h = X[1] - X[0];
    SubTable coeff(X.size());
    coeff[0]=Y;
    for (size_t i = 1; i < X.size(); i++) coeff[i] = CreateColOfSub(coeff[i - 1]);
    std::vector<double> firstSubInTable;
    std::for_each(coeff.begin(), coeff.end(), [&firstSubInTable](const std::vector<double>& col) {
        firstSubInTable.push_back(col.front());
    });
    return new ResNewtonPol2D({X.front(),X.back()},h,std::move(firstSubInTable));
    return nullptr;
}
std::vector<double> NewtonPolynomInterp::CreateColOfSub(const std::vector<double>& col) {
    std::vector<double> res(col.size());
    std::transform(col.cbegin(), col.cend() - 1, col.cbegin() + 1, res.begin(),
                    [](const double& a, const double& b) { return b-a; });
    return res;
}