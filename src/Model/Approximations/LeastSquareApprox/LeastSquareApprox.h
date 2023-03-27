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
    SLEAlgorithm slea;

 public:
    explicit LeastSquareApprox(size_t degree = 6) : degree_(degree) {}
// [[nodiscard]] 
    virtual IGraphByDiscrete2D *CreateFunction(const std::vector<double> &X, const std::vector<double> &Y) {
        Matrix coeffXMatrix(degree_, degree_+1);
        SetValuesForXMatrix(coeffXMatrix, X, Y);
        SetValuesForYMatrix(coeffXMatrix, X, Y);
        return new ResLSA2D(slea.start(coeffXMatrix).answer);
    }

 private:
    void SetValuesForXMatrix(Matrix &matrix, const std::vector<double> &X,
                             const std::vector<double> &Y) const noexcept {
        std::vector<double> temp(X.size(), 1);
        size_t degreeForX = 0, indexLastRow = matrix.GetRows() - 1;
        matrix(0, 0) = X.size();
        for (size_t diag = 1; diag < (degree_ * 2); diag++) {
            std::transform(temp.cbegin(), temp.cend(), X.cbegin(), temp.begin(),
                           [](const auto &a, const auto &b) { return a * b; });
            
            double valueForDiag = std::accumulate(temp.begin(), temp.end(), 0.00);
            long i = (indexLastRow > diag ? diag : indexLastRow),
                 j = (diag > indexLastRow) ? (diag - indexLastRow) : 0;
            
            for (; i >= 0 && j <= indexLastRow; i--, j++) {
                matrix(i, j) = valueForDiag;
            }
        }
    }
    void SetValuesForYMatrix(Matrix &matrix, const std::vector<double> &X,
                             const std::vector<double> &Y) const noexcept {
        std::vector<double> temp(Y);

        matrix(0, matrix.GetCols()-1) = std::accumulate(temp.cbegin(), temp.cend(), 0.0);

        for (size_t i = 1; i < degree_; i++) {
            std::transform(temp.cbegin(), temp.cend(), X.cbegin(), temp.begin(),
                        [](const auto &a, const auto &b) { return a * b; });
            matrix(i, matrix.GetCols()-1) = std::accumulate(temp.cbegin(), temp.cend(), 0.0);
        }
    }
};
