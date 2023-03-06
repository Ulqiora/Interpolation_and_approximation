#pragma once
#include "../../Matrix/Matrix.h"
#include "../IInterpolation2D.h"
class ResCubicSplines2D;
/*
Если у нас число точек n, то:
1) число интервалов N=n-1
2) по первому требовению выставляются первые 2N уравнений
*/
class CubicSplines : public Interpolation {
 public:
    enum Coeff { A = 0, B, C, D };
    struct CubicSplinesCoeffOneInterval {
        double A, B, C, D;
    };
    [[nodiscard]] virtual IGraphByDiscrete2D* CreateFunction(const std::vector<double>& X, const std::vector<double>& Y);

 private:
    void SetCoeffByFirstClaim(Matrix& coeffs, std::vector<double>& Ys, const std::vector<double>& X,
                              const std::vector<double>& Y, std::vector<double>& polinomCoeff);
    void SetCoeffBySecondClaim(Matrix& coeffs, const std::vector<double>& X, const std::vector<double>& Y);
    void SetCoeffByThirdClaim(Matrix& coeffs, const std::vector<double>& X, const std::vector<double>& Y);
    void SimplifyMatrixCoeffs(Matrix& coeffs);
    Matrix SimplifyMatrixYs(std::vector<double>& Ys, const std::vector<double>& polinomCoeff);
    std::vector<CubicSplinesCoeffOneInterval> CreateResult(std::vector<double>& polinomCoeff,
                                                           Matrix OtherCoefficient);

};