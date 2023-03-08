#pragma once
#include <vector>

#include "../IInterpolation2D.h"

class NewtonPolynomInterp : public IInterpolation{
 public:
    using SubTable = std::vector<std::vector<double>>;
    // [[nodiscard]]
    virtual IGraphByDiscrete2D* CreateFunction(const std::vector<double>& X,const std::vector<double>& Y);
 private:
    std::vector<double> CreateColOfSub(const std::vector<double>& col);
};