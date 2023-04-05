#pragma once
#include <iostream>
#include <stdexcept>

#include "../../IGraphByDiscrete2D.h"
#include "NewtonPolynomInterp.h"
class ResNewtonPol2D : public IGraphByDiscrete2D {
    std::vector<double> X_;
    std::vector<double> Y_;
    double step_;
    NewtonPolynomInterp::SubTable coeffs_;
    size_t degree_;

 public:
    ResNewtonPol2D(const std::vector<double> X, const std::vector<double> Y, double step,
                   NewtonPolynomInterp::SubTable&& coeffs, size_t degree)
        : X_(X), Y_(Y), step_(step), coeffs_(coeffs), degree_(degree) {}
    double calc(double arg) const override {
        if (arg < X_.front() || arg > X_.back())
            throw std::invalid_argument("The argument does not belong to the desired segment");
        int start = FindStart(arg);
        size_t end = std::min(degree_+start, X_.size());
        // std::cout<<"Start : "<<start<<'\n';
        // std::cout<<"End : "<<end<<'\n';
        long double result = coeffs_[0][start];
        long double q = (arg - X_[start]) / static_cast<long double>(step_);
        // std::cout<<"q = "<<q<<'\n';
        // std::cout<<"result = "<<result<<'\n';
        size_t factorial=1;
        double q_n=q;
        for (int i = 1; i <= end-start && i<X_.size(); i++) {
            std::cout<<i<<"     "<<q_n<<"    "<<coeffs_[i][start]<<'\n';
            result+=(coeffs_[i][start]*q_n)/factorial;
            factorial*=(i+1);
            q_n*=(q-i);
        }
        return result;
    }

 private:
    int FindStart(double x) const {
        // std::cout<<"Start :     "<<x;
        auto start = --std::find_if(X_.begin(),X_.end(),[x](auto temp){return temp>x;});
        std::cout<<"find_if : "<<*start<<'\n';
        std::cout<<"distance : "<<std::distance(start,X_.end())<<'\n';
        std::cout<<"distance : "<<std::distance(X_.begin(), start)<<'\n';
        return std::distance(X_.begin(), start);
    }
    size_t FindNearest(double x)const  {
        double minimum = abs(X_[0] - x);
        size_t nearestIndex = 0;
        for (size_t i = 1; i < X_.size() && minimum != 0; i++) {
            double current = abs(X_[i] - x);
            if (current < minimum) {
                minimum = current;
                nearestIndex = i;
            }
        }
        return nearestIndex;
    }
    static long double factorial(long double n) {
        long double f = 1;
        for (int i = 1; i <= n; ++i) f *= i;
        return f;
    }
};