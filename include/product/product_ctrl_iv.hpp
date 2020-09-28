#ifndef PRODUCT_CTRL_IV_HPP
#define PRODUCT_CTRL_IV_HPP

#include <memory>
#include <string>

class ProductView;

class IVProductCtrl {
public:
    virtual void SetView(ProductView* view) = 0;
    virtual void Show() = 0;
    virtual void Save() = 0;
    virtual bool AddProduct(std::string name, float p, float f, float c) = 0;
    virtual ~IVProductCtrl() {};
};
#endif
