#pragma once
#include "../../IGraphByDiscrete2D.h"

class ResLSA2D : public IGraphByDiscrete2D {
 private:
    std::vector<long double> coeffs_;

 public:
    ResLSA2D(const std::vector<long double> &coeff) : coeffs_(coeff) {}
    double calc(double x) const {
        double res = coeffs_[0];
        for (size_t i = 1; i < coeffs_.size(); i++) res += (coeffs_[i] * std::pow(x, i));
        return res;
    }
};