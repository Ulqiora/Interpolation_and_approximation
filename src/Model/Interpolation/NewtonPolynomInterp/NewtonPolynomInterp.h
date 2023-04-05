#pragma once
#include <iostream>
#include <vector>

#include "../IInterpolation2D.h"

class NewtonPolynomInterp : public IInterpolation {
   public:
    using SubTable = std::vector<std::vector<double>>;
    [[nodiscard]] virtual IGraphByDiscrete2D* CreateFunction(
        const std::vector<double>& X, const std::vector<double>& Y);
    size_t degree_;
    explicit NewtonPolynomInterp(size_t degree=6):degree_(degree){}
   private:
    std::vector<double> CreateColOfSub(const std::vector<double>& col,
                                       size_t i);
};