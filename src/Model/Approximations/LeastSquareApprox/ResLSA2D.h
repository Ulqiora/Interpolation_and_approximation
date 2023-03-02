#pragma once
#include "../../IGraphByDiscrete2D.h"

class ResLSA2D : public IGraphByDiscrete2D
{
private:
    double a;
    double b;
    std::function<double(double)> func_;

public:
    ResLSA2D(const std::pair<double, double> &coeff, std::function<double(double)> func) : a(coeff.first), b(coeff.second), func_(func) {}
    double calc(double x) const { return func_(x) * a + b; }
};