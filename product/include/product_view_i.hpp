#ifndef PRODUCT_IVIEW_HPP
#define PRODUCT_IVIEW_HPP

#include <vector>
#include <string>

class IProductView {
public:
    virtual void Show(std::vector<std::vector<std::string>> records) = 0;
    virtual void Run() = 0;
    virtual std::string GetName() = 0;
    virtual std::string GetProtein() = 0;
    virtual std::string GetFat() = 0;
    virtual std::string GetCarbo() = 0;
    virtual ~IProductView() {};
};
#endif
