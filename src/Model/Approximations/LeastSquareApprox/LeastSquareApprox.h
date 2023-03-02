#pragma once
#include <map>
#include <cmath>

#include "../IApproximation2D.h"
#include "ResLSA2D.h"
#include "FuncCalcCoeff/ExpFuncCalcCoeff.h"
#include "FuncCalcCoeff/HyperbolicFuncCalcCoeff.h"
#include "FuncCalcCoeff/LinearFuncCalcCoeff.h"
#include "FuncCalcCoeff/LogFuncCalcCoeff.h"
#include "FuncCalcCoeff/StepFuncCalcCoeff.h"

class LeastSquareApprox : public IApproximation2D
{
public:
    enum class FuncForLSA
    {
        LINEAR,
        EXPONENTIAL,
        STEP,
        HYPERBOLIC,
        LOGARITHMIC
    };

    LeastSquareApprox(FuncForLSA func) : func_(func) {}
    
    [[nodiscard]] virtual IGraphByDiscrete2D *CreateFunction(const std::vector<double> &X, const std::vector<double> &Y)
    {
        auto coeffs = funcCalcCoeff_[func_](X, Y);
        return new ResLSA2D(coeffs, functions_[func_]);
    }

private:
    FuncForLSA func_;
    using FuncForCalcCoeff = std::function<std::pair<double, double>(const std::vector<double> &, const std::vector<double> &)>;
    std::map<FuncForLSA, FuncForCalcCoeff> funcCalcCoeff_{{FuncForLSA::LINEAR, LinearFuncCalcCoeff()},
                                                          {FuncForLSA::EXPONENTIAL, ExpFuncCalcCoeff()},
                                                          // {FuncForLSA::STEP, StepFuncCalcCoeff()},
                                                          {FuncForLSA::HYPERBOLIC, HyperbolicFuncCalcCoeff()},
                                                          {FuncForLSA::LOGARITHMIC, LogFuncCalcCoeff()}};
    std::map<FuncForLSA, std::function<double(double)>> functions_{{FuncForLSA::LINEAR, [](double x) { return x; }},
                                                                   {FuncForLSA::EXPONENTIAL, [](double x) { return std::exp(x); }},
                                                                   // {FuncForLSA::STEP, },
                                                                   {FuncForLSA::HYPERBOLIC, [](double x) { return 1 / x; }},
                                                                   {FuncForLSA::LOGARITHMIC, [](double x) { return std::log(x); }}};
};
