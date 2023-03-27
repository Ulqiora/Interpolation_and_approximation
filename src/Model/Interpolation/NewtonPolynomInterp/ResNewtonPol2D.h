#pragma once
#include <stdexcept>
#include <iostream>
#include "../../IGraphByDiscrete2D.h"
#include "NewtonPolynomInterp.h"
class ResNewtonPol2D : public IGraphByDiscrete2D {
    std::pair<double, double> Xminmax_;
    double step_;
    std::vector<double> coeffs_;

 public:
    ResNewtonPol2D(std::pair<double, double> maxmin, double step, std::vector<double>&& coeffs)
        : Xminmax_(maxmin), step_(step), coeffs_(coeffs) {}
    double calc(double arg) const override {
        if(arg<Xminmax_.first||arg>Xminmax_.second)
            throw std::invalid_argument("The argument does not belong to the desired segment");
        double q = (arg - Xminmax_.first)/step_,res=coeffs_.front(),factorial=1;
        double q_n=q;
        for(size_t i=1;i<coeffs_.size();i++){
            res+=(coeffs_[i]*q_n)/factorial;
            factorial*=(i+1);
            q_n*=(q-i);
        } 
        return res;
    }
};