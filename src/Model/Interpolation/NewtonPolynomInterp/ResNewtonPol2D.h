#pragma once
#include <stdexcept>
#include <iostream>
#include "../../IGraphByDiscrete2D.h"
#include "NewtonPolynomInterp.h"
class ResNewtonPol2D : public IGraphByDiscrete2D {
    std::pair<double, double> X_maxmin_;
    double step_;
    std::vector<double> coeffs_;

 public:
    ResNewtonPol2D(std::pair<double, double> maxmin, double step, std::vector<double>&& coeffs)
        : X_maxmin_(maxmin), step_(step), coeffs_(coeffs) {}
    double calc(double arg) const override {
        if(arg<X_maxmin_.first||arg>X_maxmin_.second)
            throw std::invalid_argument("The argument does not belong to the desired segment");
        double q = (arg - X_maxmin_.first)/step_,res=coeffs_.front(),factorial=1;
        for(size_t i=1;i<coeffs_.size();i++){
            std::cout<<coeffs_[i]<<"  "<<q<<"  "<<factorial<<"\n";
            res+=(coeffs_[i]*q)/factorial;
            factorial*=(i+1);
            q*=(q-i);
        }
        return res;
    }
};