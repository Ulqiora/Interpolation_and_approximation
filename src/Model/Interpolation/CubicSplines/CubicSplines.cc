#include "CubicSplines.h"

#include "ResCubicSplines2D.h"
IGraphByDiscrete2D *CubicSplines::CreateFunction(const std::vector<double> &X,
                                                 const std::vector<double> &Y) {
    size_t size_=X.size()-1;
    Matrix coeffs(size_ - 1, size_);
    std::vector<std::vector<double>> res(4,std::vector<double>(size_));
    std::vector<double> h(size_);
    for (size_t i = 0; i < size_; i++) {
        h[i]=X[i + 1] - X[i];
        // std::cout<<h[i]<<' ';
    }
    // std::cout<<'\n';
    for (size_t i = 1, j = 0; i < size_; i++, j++) {
        if (i > 1) coeffs(j, j - 1) = 1.0 / 3.0 * h[i - 1];
        coeffs(j, j) = 2.0 / 3.0 * (h[i - 1] + h[i]);
        if (i < size_ - 1) coeffs(j, j + 1) = 1.0 / 3.0 * h[i];
        coeffs(j, size_-1) =(Y[i + 1] - Y[i]) / h[i] -
                            (Y[i] - Y[i - 1]) / h[i-1];
    }
    // coeffs.print(std::cout);
    res[C] = slea.start(coeffs).answer;
    res[C].insert(res[C].begin(), 0.0);
    // std::cout<<"KU"<<res[A].size()<<"  "<<res[B].size()<<"  "<<res[C].size()<<"  "<<res[D].size()<<'\n';
    for (unsigned i = 0; i < size_; i++) {
        res[A][i] = Y[i];
        res[B][i] = (Y[i+1] - Y[i]) / h[i] -
                1.0 / 3.0 * (2.0 * res[C][i] + res[C][i + 1]) * h[i];
        res[D][i] = (res[C][i + 1] - res[C][i]) / (3.0 * h[i]);
    }
    // for (const auto i : res.answer) std::cout << i<<' ';
    return new ResCubicSplines2D(X, std::move(res));
    return nullptr;
}