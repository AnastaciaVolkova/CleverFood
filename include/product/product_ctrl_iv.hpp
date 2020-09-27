#ifndef PRODUCT_CTRL_IV_HPP
#define PRODUCT_CTRL_IV_HPP

#include <memory>

class ProductView;

class IVProductCtrl {
public:
    virtual void SetView(ProductView* view) = 0;
    virtual void Show() = 0;
};
#endif
