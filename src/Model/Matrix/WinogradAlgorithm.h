#pragma once
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

#include "Matrix.h"
using Factor = std::vector<double>;

void correctJoin(std::thread& t);

class WinogradAlgorithm {
 private:
    const Matrix* firstMatrix;
    const Matrix* secondMatrix;
    int halfSize = 0;
    int numOfThreads = 0;
    std::vector<std::thread> threads;

 private:
    bool checkSize(const Matrix&, const Matrix&);

 private:
    void calcRowFactor(Factor&);
    void calcColFactor(Factor&);
    void calculationWithNumberOfThreads(Matrix&, const Factor&, const Factor&);
    void calcRowValues(Matrix&, const Factor&, const Factor&, int i);
    void addToOddMatrix(Matrix&);

 public:
    Matrix runWithSetNumOfThreads( const Matrix& first, const Matrix& second,int numberThreads);
};