#pragma once
#include <vector>
class IGraphByDiscrete2D;

class IGraphing2DByDiscrete{
    public:
    [[nodiscard]] virtual IGraphByDiscrete2D* CreateFunction(const std::vector<double>& X,const std::vector<double>& Y) = 0;
};

