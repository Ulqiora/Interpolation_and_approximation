#include "WinogradAlgorithm.h"
void correctJoin(std::thread& t) {
    if (t.joinable()) t.join();
}

Matrix WinogradAlgorithm::runWithSetNumOfThreads(const Matrix& first,const Matrix& second,int numberThreads) {
    if ((numberThreads % 4 == 0 && numberThreads <= (int)std::thread::hardware_concurrency()) ||
        numberThreads == 2) {
        numOfThreads = numberThreads;
    } else {
        throw std::invalid_argument("Incorrect number of threads!");
    }
    firstMatrix=&first;
    secondMatrix=&second;
    threads.resize(numOfThreads);
    Matrix result(firstMatrix->GetRows(), secondMatrix->GetCols());
    Factor row(firstMatrix->GetRows()), col(secondMatrix->GetCols());
    threads[0] = std::move(std::thread(&WinogradAlgorithm::calcRowFactor, this, std::ref(row)));
    threads[1] = std::move(std::thread(&WinogradAlgorithm::calcColFactor, this, std::ref(col)));
    threads[0].join(), threads[1].join();
    calculationWithNumberOfThreads(result, row, col);
    if ((2 * halfSize) != firstMatrix->GetCols()) addToOddMatrix(result);
    return result;
}

void WinogradAlgorithm::calculationWithNumberOfThreads(Matrix& result, const Factor& row,
                                                       const Factor& col) {
    int i = 0;
    for (i = 0; i < firstMatrix->GetRows(); ++i) {
        correctJoin(threads[i % (threads.size() - 1)]);
        threads[i % (threads.size() - 1)] = std::move(std::thread(
            &WinogradAlgorithm::calcRowValues, this, std::ref(result), std::ref(row), std::ref(col), i));
    }
    for (int j = 0; j < i; ++j) {
        correctJoin(threads[j % (threads.size())]);
    }
}

void WinogradAlgorithm::calcRowValues(Matrix& result, const Factor& row, const Factor& col, int i) {
    for (int j = 0; j < secondMatrix->GetCols(); ++j) {
        result(i, j) = -row[i] - col[j];
        for (int k = 0; k < halfSize; ++k) {
            result(i, j) += ((*firstMatrix)(i, 2 * k) + (*secondMatrix)(2 * k + 1, j)) *
                            ((*firstMatrix)(i, 2 * k + 1) + (*secondMatrix)(2 * k, j));
        }
    }
}

bool WinogradAlgorithm::checkSize(const Matrix& first, const Matrix& second) {
    if (first.GetCols() == second.GetRows()) return true;
    return false;
}

void WinogradAlgorithm::calcRowFactor(Factor& row) {
    for (int i = 0; i < firstMatrix->GetRows(); ++i) {
        row[i] = (*firstMatrix)(i, 0) * (*firstMatrix)(i, 1);
        for (int j = 1; j < halfSize; ++j) {
            row[i] += ((*firstMatrix)(i, 2 * j) * (*firstMatrix)(i, 2 * j + 1));
        }
    }
}

void WinogradAlgorithm::calcColFactor(Factor& col) {
    for (int i = 0; i < secondMatrix->GetCols(); ++i) {
        col[i] = (*secondMatrix)(0, i) * (*secondMatrix)(1, i);
        for (int j = 1; j < halfSize; ++j) {
            col[i] += ((*secondMatrix)(2 * j, i) * (*secondMatrix)(2 * j + 1, i));
        }
    }
}

void WinogradAlgorithm::addToOddMatrix(Matrix& result) {
    for (int i = 0; i < result.GetRows(); ++i) {
        for (int j = 0; j < result.GetCols(); ++j) {
            result(i, j) +=
                ((*firstMatrix)(i, firstMatrix->GetCols() - 1) * (*secondMatrix)(secondMatrix->GetRows() - 1, j));
        }
    }
}

