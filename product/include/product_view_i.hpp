#ifndef PRODUCT_IVIEW_HPP
#define PRODUCT_IVIEW_HPP

#include <vector>
#include <string>

class IProductView {
public:
    virtual void Show(std::vector<std::vector<std::string>> records) = 0;
    virtual void Run() = 0;
    virtual std::string GetNameToAdd() = 0;
    virtual std::string GetProteinToAdd() = 0;
    virtual std::string GetFatToAdd() = 0;
    virtual std::string GetCarboToAdd() = 0;
    virtual ~IProductView() {};
};
#endif
