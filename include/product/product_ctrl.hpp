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
    ProductView* view_;
    std::string store_filename_;
    std::unique_ptr<ProductMdl> model_;
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

    //! Save to memory
    void Save() override;

    //! Store new records to databased.
    void Store(std::vector<std::vector<std::string>>& records) override;

    /*!
    * \brief Add product to products base.
    * \param name Product name.
    * \param p Protein in gram per 100 gram of product
    * \param p Fet in gram per 100 gram of product
    * \param p Carbohydrate in gram per 100 gram of product
    */
    bool AddProduct(std::string name, float p, float f, float c) override;

    /*!
    * \brief Update product in products base.
    * \param name Product name to update.
    * \param parameter Parameter to update.
    * \param meaning New meaning of parameter.
    * \return true if update was sucessfull.
    */
    bool UpdateProduct(std::string name, Parameter parameter, std::string meaning) override;

    /*!
    * \brief Delete product.
    * \param name Name of product to delete.
    * \return true if delete operation was successfull.
    */
    bool DeleteProduct(std::string name) override;
};
#endif
