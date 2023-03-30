    #include "LeastSquareApprox.h"
    [[nodiscard]] IGraphByDiscrete2D *LeastSquareApprox::CreateFunction(const std::vector<double> &X, const std::vector<double> &Y) {
        Matrix Xmatrix(degree_, degree_), Ymatrix(degree_,1);
        SetValuesForXMatrix(Xmatrix, X, Y);
        SetValuesForYMatrix(Ymatrix, X, Y);
        return new ResLSA2D(slea_.GetResult(Xmatrix,Ymatrix));
    }

    void LeastSquareApprox::SetValuesForXMatrix(Matrix &matrix, const std::vector<double> &X,
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
    void LeastSquareApprox::SetValuesForYMatrix(Matrix &matrix, const std::vector<double> &X,
                             const std::vector<double> &Y) const noexcept {
        std::vector<double> temp(Y);
        matrix(0, 0) = std::accumulate(temp.cbegin(), temp.cend(), 0.0);
        for (size_t i = 1; i < degree_; i++) {
            std::transform(temp.cbegin(), temp.cend(), X.cbegin(), temp.begin(),
                        [](const auto &a, const auto &b) { return a * b; });
            matrix(i, 0) = std::accumulate(temp.cbegin(), temp.cend(), 0.0);
        }
    }