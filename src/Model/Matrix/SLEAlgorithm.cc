#include "SLEAlgorithm.h"

void SLEAlgorithm::solveGauss() {
    int i;
    std::vector<std::thread> allThreads;
    for (i = 0; i < mSize; i++) {
        std::thread myThread(&SLEAlgorithm::oneThread, this, i, i);
        allThreads.push_back(std::move(myThread));
    }
    for (size_t j = 0; j < allThreads.size(); j++) {
        allThreads[j].join();
    }

    for (i = mSize - 1; i >= 0; i--) {
        findAnswers(i);
    }

    for (i = 0; i < mSize; i++) {
        if (std::isnan(result.answer[i])) {
            std::cout<<"nan: "<<i<<'\n';
            throw std::out_of_range("Cannot solve this matrix");
        }
    }
}

void SLEAlgorithm::oneThread(int row, int col) {
    for (int i = row; i < mSize; i++) {
        double x = 1.0 / data_(i, col);
        for (int j = 0; j < data_.GetCols(); j++) {
            data_(i, j) *= x;
        }
    }
    for (int i = row + 1; i < mSize; i++) {
        for (int j = 0; j < data_.GetCols(); j++) {
            data_(i, j) -= data_(row, j);
        }
    }
}

void SLEAlgorithm::findAnswers(int index) {
    double res = data_(index, mSize);
    for (int i = index + 1; i < mSize; i++) {
        res -= data_(index, i) * result.answer[i];
    }
    result.answer[index] = res;
}

SLEAlgorithm::SLEResult SLEAlgorithm::start(const Matrix& matrix) {
    data_ = matrix;
    dataOld = matrix;
    mSize = matrix.GetRows();
    result.answer.resize(mSize);
    if (mSize > 0) {
        data_ = dataOld;
        try {
            solveGauss();
        } catch (std::exception& e) {
            throw;
        }
    } else {
        throw std::out_of_range("Matrix is not set");
    }
    return result;
}

const std::vector<double>& SLEAlgorithm::getAnswer() { return result.answer; }

void SLEAlgorithm::printAnswer() {
    if (result.answer.size() > 0) {
        for (unsigned int i = 0; i < result.answer.size(); i++) {
            std::cout << result.answer[i] << ' ';
        }
        std::cout << std::endl;
    } else {
        throw std::out_of_range("There is no answer");
    }
}

