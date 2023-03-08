#include "CubicSplines.h"

#include "ResCubicSplines2D.h"
IGraphByDiscrete2D* CubicSplines::CreateFunction(const std::vector<double>& X,
                                                 const std::vector<double>& Y) {
    Matrix coeffs((X.size() - 1) * 4);
    std::vector<double> polinomCoeff((X.size() - 1) * 4);
    std::vector<double> Ys((X.size() - 1) * 4);
    SetCoeffByFirstClaim(coeffs, Ys, X, Y, polinomCoeff);
    SetCoeffBySecondClaim(coeffs, X, Y);
    SetCoeffByThirdClaim(coeffs, X, Y);
    auto MatrixYs = SimplifyMatrixYs(Ys, polinomCoeff);
    SimplifyMatrixCoeffs(coeffs);
    CreateResult(polinomCoeff, coeffs.Inverse() * MatrixYs);
    return new ResCubicSplines2D(X, CreateResult(polinomCoeff, coeffs.Inverse() * MatrixYs));
}

void CubicSplines::SetCoeffByFirstClaim(Matrix& coeffs, std::vector<double>& Ys,
                                        const std::vector<double>& X, const std::vector<double>& Y,
                                        std::vector<double>& polinomCoeff) {
    size_t NumOfInterval = X.size() - 1;
    for (size_t i = 0; i < NumOfInterval; i++) {
        coeffs(i, A + i * 4) = Y[i];
        polinomCoeff[A + i * 4] = Y[i];
        Ys[i] = Y[i];
        coeffs(i + NumOfInterval, A + i * 4) = 1;
        coeffs(i + NumOfInterval, B + i * 4) = X[i + 1] - X[i];
        coeffs(i + NumOfInterval, C + i * 4) = (X[i + 1] - X[i]) * (X[i + 1] - X[i]);
        coeffs(i + NumOfInterval, D + i * 4) = (X[i + 1] - X[i]) * (X[i + 1] - X[i]) * (X[i + 1] - X[i]);
        Ys[i + NumOfInterval] = Y[i + 1] - Y[i];
    }
}
void CubicSplines::SetCoeffBySecondClaim(Matrix& coeffs, const std::vector<double>& X,
                                         const std::vector<double>& Y) {
    size_t NumOfInterval = X.size() - 2;
    size_t startpoint = (X.size() - 1) * 2;
    for (size_t i = 0; i < NumOfInterval; i++) {
        coeffs(i + startpoint, B + i * 4) = 1;
        coeffs(i + startpoint, C + i * 4) = 2 * (X[i + 1] - X[i]);
        coeffs(i + startpoint, D + i * 4) = 3 * (X[i + 1] - X[i]) * (X[i + 1] - X[i]);
        coeffs(i + startpoint, B + (i + 1) * 4) = -1;
        coeffs(i + startpoint + NumOfInterval, C + i * 4) = 2;
        coeffs(i + startpoint + NumOfInterval, D + i * 4) = 6 * (X[i + 1] - X[i]);
        coeffs(i + startpoint + NumOfInterval, C + (i + 1) * 4) = -2;
    }
}
void CubicSplines::SetCoeffByThirdClaim(Matrix& coeffs, const std::vector<double>& X,
                                        const std::vector<double>& Y) {
    coeffs(coeffs.GetRows() - 1, C + (X.size() - 2) * 4) = 2;
    coeffs(coeffs.GetRows() - 1, D + (X.size() - 2) * 4) = 6 * (X[X.size() - 1] - X[X.size() - 2]);
}
void CubicSplines::SimplifyMatrixCoeffs(Matrix& coeffs) {
    for (int i = (coeffs.GetRows() / 4) - 1; i >= 0; i--) coeffs = coeffs.CreateMinor(i, i * 4 + A);
    coeffs = coeffs.CreateMinor(coeffs.GetRows() - 2, 1);
}
Matrix CubicSplines::SimplifyMatrixYs(std::vector<double>& Ys, const std::vector<double>& polinomCoeff) {
    for (int i = Ys.size() / 4 - 1; i >= 0; i--) {
        Ys.erase(Ys.begin());
    }
    Ys.erase(Ys.begin() + Ys.size() - 2);
    Matrix res(Ys.size(), 1);
    for (int i = 0; i < Ys.size(); i++) res(i, 0) = Ys[i];
    return res;
}
std::vector<CubicSplines::CoeffOneInterval> CubicSplines::CreateResult(
    std::vector<double>& polinomCoeff, Matrix OtherCoefficient) {
    polinomCoeff[1] = OtherCoefficient(0, 0);
    polinomCoeff[3] = OtherCoefficient(1, 0);
    for (int i = 2, interval = 1; i < OtherCoefficient.GetRows(); i += 3, interval++) {
        polinomCoeff[4 * interval + B] = OtherCoefficient(i, 0);
        polinomCoeff[4 * interval + C] = OtherCoefficient(i + 1, 0);
        polinomCoeff[4 * interval + D] = OtherCoefficient(i + 2, 0);
    }
    std::vector<CoeffOneInterval> res(polinomCoeff.size() / 4);
    for (int i = 0; i < res.size(); i++) {
        res[i].A = polinomCoeff[i * 4 + A];
        res[i].B = polinomCoeff[i * 4 + B];
        res[i].C = polinomCoeff[i * 4 + C];
        res[i].D = polinomCoeff[i * 4 + D];
    }
    return res;
}