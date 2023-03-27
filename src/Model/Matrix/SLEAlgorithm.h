#pragma once

#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "Matrix.h"

class SLEAlgorithm {
 public:
    struct SLEResult {
        std::vector<double> answer;
    };

 private:
    Matrix data_, dataOld;
    SLEResult result;
    int mSize = 0;

 public:
    SLEAlgorithm() {}
    SLEResult start(const Matrix& matrix);
    const std::vector<double>& getAnswer();
    void printAnswer();

 private:
    void solveGauss();
    void oneThread(int row, int col);
    void forwardStep();
    void backStep();
    void findAnswers(int index);
};