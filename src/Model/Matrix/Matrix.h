#pragma once
#include <cmath>
#include <iostream>
#include <iomanip>
class Matrix {
    friend Matrix operator*(const Matrix& other, double const num);
    friend Matrix operator*(double const num, const Matrix& other);

 private:
    size_t rows_, cols_;
    double** matrix_;
    [[nodiscard]] double** NewMatrix(size_t rows, size_t cols) const;
    void DestroyMatrix();
    void CopyMatrix(double** matrix_copy);

 public:
    [[nodiscard]] Matrix CreateMinor(size_t row, size_t column) const;
    Matrix();
    Matrix(size_t rows, size_t cols);
    Matrix(size_t n);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();

    Matrix operator=(const Matrix& other);

    bool Equal(const Matrix& other) const;
    bool operator==(const Matrix& other) const;
    // sum
    void Sum(const Matrix& other);
    [[nodiscard]] Matrix operator+(const Matrix& other) const;
    Matrix operator+=(const Matrix& other);
    // sub
    void Sub(const Matrix& other);
    [[nodiscard]] Matrix operator-(const Matrix& other) const;
    Matrix operator-=(const Matrix& other);
    // mul
    void Mul(const double num);
    void Mul(const Matrix& other);
    [[nodiscard]] Matrix operator*(const Matrix& other) const;
    Matrix operator*=(const Matrix& other);
    Matrix operator*=(const double num);
    // operation
    [[nodiscard]] Matrix Transpose() const;
    [[nodiscard]] Matrix CalcComplements() const;
    double Determinant() const;
    [[nodiscard]] Matrix Inverse() const;

    double& operator()(size_t i, size_t j) const;
    // other
    size_t GetRows() const;
    size_t GetCols() const;
    void SetRows(size_t rows);
    void SetCols(size_t cols);
    void print(std::basic_ostream<char>& stream) const noexcept;
    void SetToIdentity(size_t size);
    static std::pair<Matrix, Matrix> CreateLUMatricies(const Matrix& matrix) {
        //L - first
        if (matrix.GetCols() != matrix.GetRows()) std::logic_error("This matrix is not square!");
        std::pair<Matrix, Matrix> res;
        auto size(matrix.GetCols());
        res.first.SetToIdentity(size),res.second.SetToIdentity(size);
        size_t stop=0;
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                double mul = 0;
                stop = i <= j ? i : j;
                for (size_t k = 0; k < stop; k++)
                    mul += (res.first(i, k) * res.second(k, j));
                if (i <= j)
                    res.second(i, j) = matrix(i, j) - mul;
                else
                    res.first(i, j) = (matrix(i, j) - mul) / res.second(j, j);
            }
        }
        return res;
    }
};
