#ifndef PRODUCT_CTRL_HPP_
#define PRODUCT_CTRL_HPP_
#include "product/product_mdl.hpp"
#include "product/product_ctrl_iv.hpp"
#include "product/product_ctrl_im.hpp"
#include <memory>
#include <string>

class ProductView;


class ProductCtrl :public IMProductCtrl, public IVProductCtrl {
private:
    std::unique_ptr<ProductMdl> model_;
    ProductView* view_;
    std::string store_filename_;
public:
    ProductCtrl() :ProductCtrl("../data/products.txt") {};

    ProductCtrl(std::string file);
    /*!
    * \brief Set view for controller.
    * \param view Pointer to view. This view will be manipulated by controller.
    */
    void SetView(ProductView* view) override;

    //! Show all product elements in view.
    void Show() override;

    /*!
    * \brief Add product to products base.
    * \param name Product name.
    * \param p Protein in gram per 100 gram of product
    * \param p Fet in gram per 100 gram of product
    * \param p Carbohydrate in gram per 100 gram of product
    */
    bool AddProduct(std::string name, float p, float f, float c) override;
};
#endif
