#pragma once
#include "../../IGraphByDiscrete2D.h"
#include "CubicSplines.h"

class ResCubicSplines2D : public IGraphByDiscrete2D {
   private:
    std::vector<double> x_;
    std::vector<std::vector<long double>> coeffs_;

   public:
    ResCubicSplines2D(const std::vector<double>& X,
                      std::vector<std::vector<long double>>&& coeffs)
        : x_(X), coeffs_(coeffs) {}
    double calc(double arg) const {
        if(arg<x_.front()||arg>x_.back())
            throw std::invalid_argument(
                "This point does not belong to the interpolation interval!");
        auto founded =
            std::find_if(x_.begin(), x_.end(),
                         [arg](const auto& value) { return arg <= value; });
        int now;
        if (founded == x_.begin())
            now = (founded)-x_.begin();
        else {
            now = founded - x_.begin() - 1;
            founded--;
        }
        return coeffs_[CubicSplines::Coeff::A][now] +
               coeffs_[CubicSplines::Coeff::B][now] * (arg - (*founded)) +
               coeffs_[CubicSplines::Coeff::C][now] * (arg - (*founded)) *
                   (arg - (*founded)) +
               coeffs_[CubicSplines::Coeff::D][now] * (arg - (*founded)) *
                   (arg - (*founded)) * (arg - (*founded));
    }
};