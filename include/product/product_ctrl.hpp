#ifndef PRODUCT_CTRL_HPP_
#define PRODUCT_CTRL_HPP_
#include "product/product_mdl.hpp"
#include "product/product_ctrl_iv.hpp"
#include "product/product_ctrl_im.hpp"
#include <memory>
#include <string>

class ProductView;

class ProductCtrl:public IMProductCtrl, public IVProductCtrl {
private:
    std::unique_ptr<ProductMdl> model_;
    ProductView* view_;
public:
    ProductCtrl() :ProductCtrl("../data/products.txt") {};

    ProductCtrl(std::string file);
    /*!
    \brief Set view for controller.
    \param view Pointer to view. This view will be manipulated by controller.
    */
    void SetView(ProductView* view) { view_ = view; };
};
#endif
