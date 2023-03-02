#pragma once
#include <vector>
#include <numeric>
struct LinearFuncCalcCoeff
{
    [[nodiscard]] std::pair<double, double> operator()(const std::vector<double> &X, const std::vector<double> &Y) const
    {
        double X_sum = std::accumulate(X.begin(), X.end(), 0);
        double Y_sum = std::accumulate(Y.begin(), Y.end(), 0);
        std::vector<int> temp;
        temp.reserve(X.size());
        for (size_t i = 0; i < X.size(); i++)
        {
            temp.push_back(X[i] * Y[i]);
        }
        auto XY_sum = std::accumulate(temp.begin(), temp.end(), 0);
        for (size_t i = 0; i < X.size(); i++)
        {
            temp[i]=(X[i] * X[i]);
        }
        auto X2_sum = std::accumulate(temp.begin(), temp.end(), 0);
        auto n = X.size();
        auto a = (n * XY_sum - X_sum * Y_sum) / (n * X2_sum - X_sum * X_sum);
        return std::pair<double, double>(a, (Y_sum - a * X_sum) / n);
    }
};