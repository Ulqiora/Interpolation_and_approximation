#include "Matrix.h"

Matrix::Matrix() : rows_(1), cols_(1) { this->matrix_ = NewMatrix(1, 1); }

Matrix::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols)
{
    if (this->rows_ > 0 && this->cols_ > 0)
    {
        this->matrix_ = NewMatrix(this->rows_, this->cols_);
    }
    else
    {
        this->rows_ = this->cols_ = 0;
        throw std::invalid_argument("Invalid size of matrix");
    }
}

Matrix::Matrix(const Matrix &other) : cols_(other.cols_), rows_(other.rows_)
{
    this->CopyMatrix(other.matrix_);
}

Matrix::Matrix(Matrix &&other) : cols_(other.cols_), rows_(other.rows_), matrix_(other.matrix_)
{
    other.cols_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
}

Matrix::~Matrix()
{
    if (cols_ > 0 && rows_ > 0)
    {
        this->DestroyMatrix();
    }
}

double **Matrix::NewMatrix(size_t rows, size_t cols) const
{
    double **matrix_ = new double *[rows];
    for (size_t i = 0; i < rows; i++)
    {
        matrix_[i] = new double[cols_]();
    }
    return matrix_;
}

void Matrix::DestroyMatrix()
{
    for (size_t i = 0; i < rows_; i++)
    {
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

void Matrix::CopyMatrix(double **matrix_copy)
{
    this->matrix_ = NewMatrix(this->rows_, this->cols_);
    for (size_t i = 0; i < this->rows_; i++)
    {
        for (size_t j = 0; j < this->cols_; j++)
        {
            this->matrix_[i][j] = matrix_copy[i][j];
        }
    }
}

bool Matrix::Equal(const Matrix &other) const
{
    bool ret_val = true;
    if (cols_ == other.cols_ && rows_ == other.rows_)
    {
        for (size_t i = 0; i < rows_ && ret_val == true; i++)
        {
            for (size_t j = 0; j < cols_ && ret_val == true; j++)
            {
                if (fabs(other.matrix_[i][j] - this->matrix_[i][j]) > 1e-6)
                {
                    ret_val = false;
                }
            }
        }
    }
    else
    {
        ret_val = false;
    }
    return ret_val;
}

bool Matrix::operator==(const Matrix &other) const { return Equal(other); }

void Matrix::Sum(const Matrix &other)
{
    bool ret_val = true;
    if (this->cols_ == other.cols_ && this->rows_ == other.rows_)
    {
        for (size_t i = 0; i < rows_ && ret_val == true; i++)
        {
            for (size_t j = 0; j < cols_ && ret_val == true; j++)
            {
                matrix_[i][j] += other.matrix_[i][j];
            }
        }
    }
    else
    {
        throw std::invalid_argument("Matrices are not the same size");
    }
}

Matrix Matrix::operator+(const Matrix &other) const
{
    Matrix result = *this;
    result.Sum(other);
    return result;
}

Matrix Matrix::operator+=(const Matrix &other)
{
    this->Sum(other);
    return (*this);
}
//    Sub matrix
void Matrix::Sub(const Matrix &other)
{
    bool ret_val = true;
    if (rows_ == other.rows_ && cols_ == other.cols_)
    {
        for (size_t i = 0; i < rows_ && ret_val == true; i++)
        {
            for (size_t j = 0; j < cols_ && ret_val == true; j++)
            {
                matrix_[i][j] -= other.matrix_[i][j];
            }
        }
    }
    else
    {
        throw std::invalid_argument("Matrices are not the same size");
    }
}

Matrix Matrix::operator-(const Matrix &other) const
{
    Matrix result = *this;
    result.Sub(other);
    return result;
}

Matrix Matrix::operator-=(const Matrix &other)
{
    this->Sub(other);
    return (*this);
}

void Matrix::Mul(const Matrix &other)
{
    if (this->cols_ == other.rows_)
    {
        Matrix result(this->rows_, other.cols_);
        for (size_t i = 0; i < this->rows_; i++)
        {
            for (size_t j = 0; j < other.cols_; j++)
            {
                for (size_t k = 0; k < other.rows_; k++)
                {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        *this = result;
    }
    else
    {
        throw std::invalid_argument("Matrix size error");
    }
}

void Matrix::Mul(const double num)
{
    for (size_t i = 0; i < this->rows_; i++)
    {
        for (size_t j = 0; j < this->cols_; j++)
        {
            (*this)(i, j) *= num;
        }
    }
}

Matrix operator*(const Matrix &other, double const num)
{
    Matrix result = other;
    result.Mul(num);
    return result;
}

Matrix operator*(double const num, const Matrix &other)
{
    Matrix result = other;
    result.Mul(num);
    return result;
}

Matrix Matrix::operator*(const Matrix &A) const
{
    Matrix result(*this);
    result.Mul(A);
    return result;
}

Matrix Matrix::operator*=(const Matrix &other)
{
    this->Mul(other);
    return (*this);
}

Matrix Matrix::operator*=(const double num)
{
    this->Mul(num);
    return (*this);
}

Matrix Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        this->DestroyMatrix();
        this->rows_ = other.rows_;
        this->cols_ = other.cols_;
        this->CopyMatrix(other.matrix_);
    }
    return *this;
}

double &Matrix::operator()(size_t i, size_t j) const
{
    if (i < this->rows_ && i >= 0 && j < this->cols_ && j >= 0)
    {
        return (this->matrix_[i][j]);
    }
    else
    {
        throw std::out_of_range("index matrix error");
    }
}

Matrix Matrix::Transpose() const
{
    Matrix result(this->cols_, this->rows_);
    for (size_t i = 0; i < result.rows_; i++)
    {
        for (size_t j = 0; j < result.cols_; j++)
        {
            result(i, j) = this->matrix_[j][i];
        }
    }
    return result;
}

Matrix Matrix::CreateMinor(size_t row, size_t column) const
{
    Matrix minor(this->rows_ - 1, this->cols_ - 1);
    size_t flag_row = 0;
    for (size_t i = 0; i < this->rows_; i++)
    {
        size_t flag_column = 0;
        if (i != row)
        {
            for (size_t j = 0; j < this->cols_; j++)
            {
                if (j != column)
                {
                    minor(i - flag_row, j - flag_column) = (*this)(i, j);
                }
                else
                {
                    flag_column = 1;
                }
            }
        }
        else
        {
            flag_row = 1;
        }
    }
    return minor;
}

double Matrix::Determinant() const
{
    if (this->rows_ == this->cols_)
    {
        double result = 0.0;
        if (this->cols_ != 1)
        {
            for (size_t i = 0; i < this->cols_; i++)
            {
                Matrix minor = this->CreateMinor(0, i);
                if (i % 2 == 0)
                {
                    result += minor.Determinant() * (*this)(0, i);
                }
                else
                {
                    result -= minor.Determinant() * (*this)(0, i);
                }
            }
        }
        else
        {
            result = (*this)(0, 0);
        }
        return result;
    }
    else
    {
        throw std::invalid_argument("This matrix is not square");
    }
}

Matrix Matrix::CalcComplements() const
{
    if (this->cols_ == this->rows_ && this->rows_ > 1)
    {
        Matrix result(this->rows_, this->cols_);
        for (size_t i = 0; i < this->rows_; i++)
        {
            for (size_t j = 0; j < this->cols_; j++)
            {
                Matrix minor = CreateMinor(i, j);
                if ((i + j) % 2 == 0)
                {
                    result(i, j) = minor.Determinant();
                }
                else
                {
                    result(i, j) = -minor.Determinant();
                }
            }
        }
        return result;
    }
    else
    {
        throw std::invalid_argument("Matrix is not square or size <=1");
    }
}

Matrix Matrix::Inverse() const
{
    if (!(fabs(this->Determinant()) > 1e-6))
        throw std::invalid_argument("Matrix determinant equals zero");
    Matrix result(1, 1);
    if (rows_ > 1)
    {
        Matrix comp = CalcComplements();
        Matrix cont_trans = comp.Transpose();
        cont_trans.Mul(1.0 / Determinant());
        result = cont_trans;
    }
    else
    {
        result.matrix_[0][0] = 1.0 / matrix_[0][0];
    }
    return result;
}
// Accessors & mutators
size_t Matrix::GetRows() const { return this->rows_; }

size_t Matrix::GetCols() const { return this->cols_; }

void Matrix::SetRows(size_t rows)
{
    if (rows <= 0)
        throw std::logic_error("Invalid size of rows!");
    if (rows == rows_)
        return;
    size_t minRows(rows_ < rows ? rows_ : rows);
    auto tempMatrix(NewMatrix(minRows, cols_));
    for (size_t i = 0; i < minRows; i++)
    {
        for (size_t j = 0; j < cols_; j++)
        {
            tempMatrix[i][j] = (*this)(i, j);
        }
    }
    DestroyMatrix();
    matrix_ = tempMatrix;
    rows_ = rows;
}

void Matrix::SetCols(size_t cols)
{
    if (cols <= 0)
        throw std::logic_error("Invalid size of rows!");
    if (cols_ == cols)
        return;
    size_t minCols(cols_ < cols ? rows_ : cols);
    auto tempMatrix(NewMatrix(minCols, cols_));
    for (size_t i = 0; i < minCols; i++)
    {
        for (size_t j = 0; j < cols_; j++)
        {
            tempMatrix[i][j] = (*this)(i, j);
        }
    }
    DestroyMatrix();
    matrix_ = tempMatrix;
    rows_ = cols;
}
void Matrix::print(std::basic_ostream<char>& stream) const noexcept{
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            stream << matrix_[i][j] << ' ';
        }
        stream << std::endl;
    }
}
void Matrix::SetToIdentity(size_t size){
    if(size<2) std::logic_error("Size of matrix can't me less then 2!");
    DestroyMatrix();
    rows_=size,cols_=size;
    matrix_ = NewMatrix(rows_,cols_);
    for(int i=0;i<(size);i++){
        matrix_[i][i]=1;
    }
}