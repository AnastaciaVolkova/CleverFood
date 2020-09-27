#ifndef PRODUCT_CTRL_HPP_
#define PRODUCT_CTRL_HPP_
#include "product/product_mdl.hpp"
#include "product/product_ctrl_iv.hpp"
#include "product/product_ctrl_im.hpp"

class ProductView;

class ProductCtrl:public IMProductCtrl, public IVProductCtrl {
private:
    ProductMdl* model_;
    ProductView* view_;
public:
    /*!
    \brief Transfere product to model.
    \params product Product to transfer to model.
    */
    void SetModel(ProductMdl* model) { model_ = model; }
    void SetView(ProductView* view) { view_ = view; };
};
#endif
