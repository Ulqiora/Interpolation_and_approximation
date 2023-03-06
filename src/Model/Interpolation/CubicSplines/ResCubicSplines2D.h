#pragma once
#include "../../IGraphByDiscrete2D.h"
#include "CubicSplines.h"

class ResCubicSplines2D : public IGraphByDiscrete2D {
 private:
    std::vector<double> x_;
    std::vector<CubicSplines::CubicSplinesCoeffOneInterval> coeffs_;
 public:
    ResCubicSplines2D(const std::vector<double>& X,
                      std::vector<CubicSplines::CubicSplinesCoeffOneInterval> coeffs)
        : x_(X), coeffs_(coeffs) {}
    double calc(double arg) const {
        auto founded = std::find_if(x_.begin(), x_.end(), [arg](const auto& value) { return arg <= value; });
        if ((founded == x_.begin()&&x_.front()!=(*founded)) || founded == x_.end())
            throw std::invalid_argument("This point does not belong to the interpolation interval!");
        CubicSplines::CubicSplinesCoeffOneInterval now;
        if(founded==x_.begin())
            now=coeffs_[(founded)-x_.begin()];
        else {
            now = coeffs_[founded - x_.begin() - 1];
            founded--;
        }
        return now.A + now.B * (arg - (*founded)) + now.C * (arg - (*founded)) * (arg - (*founded)) +
               now.D * (arg - (*founded)) * (arg - (*founded)) * (arg - (*founded));
    }
};