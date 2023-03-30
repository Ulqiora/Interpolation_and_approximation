#pragma once
#include "../../Matrix/Matrix.h"
#include "../../Matrix/SLEAlgorithm.h"
#include "../IInterpolation2D.h"
class ResCubicSplines2D;
/*
Если у нас число точек n, то:
1) число интервалов N=n-1
2) по первому требовению выставляются первые 2N уравнений
*/
class CubicSplines : public IInterpolation {
 public:
    enum Coeff { A = 0, B, C, D };
    SLEAlgorithm slea;
    [[nodiscard]] virtual IGraphByDiscrete2D* CreateFunction(const std::vector<double>& X, const std::vector<double>& Y);
 private:

};