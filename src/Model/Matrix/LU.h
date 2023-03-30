#pragma once

#include <vector>

#include "Matrix.h"


class LU {
 public:
  LU() = default;
  ~LU() = default;
  std::vector<long double> GetResult(Matrix& A, Matrix& B);

 private:
  Matrix L_;
  Matrix U_;
  Matrix Y_;
  void GetY(Matrix& B);
  std::vector<long double> GetX();
  long double GetXSum(Matrix& X, int n);
  long double GetYSum(Matrix& Y, int n);
  void GetLUMatrix(Matrix& A);
  void SetStandartValueLU(Matrix& L, Matrix& U);
  void SetValueLU(Matrix& L, Matrix& U, Matrix& A);
  long double GetSum(Matrix& L, Matrix& U, int lim, int i, int j);
};
