#pragma once
#include <cmath>
#include <map>
#include <numeric>

#include "../../Matrix/SLEAlgorithm.h"
#include "../../Matrix/Matrix.h"
#include "../IApproximation2D.h"
#include "ResLSA2D.h"

class LeastSquareApprox : public IApproximation2D {
    using FuncForCalcCoeff =
        std::function<std::pair<double, double>(const std::vector<double> &, const std::vector<double> &)>;
    size_t degree_;
    SLEAlgorithm slea_;

 public:
    explicit LeastSquareApprox(size_t degree = 6) : degree_(degree) {}
    [[nodiscard]] virtual IGraphByDiscrete2D *CreateFunction(const std::vector<double> &X, const std::vector<double> &Y);

 private:
    void SetValuesForXMatrix(Matrix &matrix, const std::vector<double> &X,
                             const std::vector<double> &Y) const noexcept;
    void SetValuesForYMatrix(Matrix &matrix, const std::vector<double> &X,
                             const std::vector<double> &Y) const noexcept;
};
