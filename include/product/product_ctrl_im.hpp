#ifndef PRODUCT_CTRL_IM_HPP
#define PRODUCT_CTRL_IM_HPP
#include <vector>
#include <string>

class IMProductCtrl {
public:
    virtual void Store(std::vector<std::vector<std::string>>& records) = 0;
    virtual ~IMProductCtrl() {};
};
#endif
