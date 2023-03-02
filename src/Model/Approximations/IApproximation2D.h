#pragma once
#include "../IGraphing2DByDiscrete.h"

class IApproximation2D: public IGraphing2DByDiscrete{
    public:
    [[nodiscard]] virtual IGraphByDiscrete2D* CreateFunction(const std::vector<double>& X,const std::vector<double>& Y) = 0;
};