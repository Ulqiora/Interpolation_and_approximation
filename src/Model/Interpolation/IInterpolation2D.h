#pragma once
#include "../IGraphing2DByDiscrete.h"

class IInterpolation: public IGraphing2DByDiscrete{
    [[nodiscard]] virtual IGraphByDiscrete2D* CreateFunction(const std::vector<double>& X,const std::vector<double>& Y) = 0;
};
