#pragma once
#include <vector>
#include <algorithm>
struct LogFuncCalcCoeff{
    [[nodiscard]] std::pair<double,double> operator()(const std::vector<double>& X,const std::vector<double>& Y)const{
        return std::pair<double,double>();
    }
};