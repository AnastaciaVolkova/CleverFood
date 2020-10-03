#ifndef PRODUCT_CTRL_HPP_
#define PRODUCT_CTRL_HPP_
#include "product/product_mdl.hpp"
#include "product/product_ctrl_iv.hpp"
#include "product/product_ctrl_im.hpp"
#include "product/storage_i.hpp"
#include <memory>
#include <string>

class ProductView;


class ProductCtrl :public IMProductCtrl, public IVProductCtrl {
private:
    ProductView* view_;
    std::string store_filename_;
    std::unique_ptr<ProductMdl> model_;
    std::unique_ptr<StorageI> storage_;
public:
    ProductCtrl(std::unique_ptr<StorageI> storage, std::string file);
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

    /*!
    * \brief Check correctness of a given product name.
    * \param name Given name.
    * \return Return true if a given meaning is correct.
    */
    bool CheckName(std::string name);

    /*
    * \brief Check correctness of a given protein meaning.
    * \param meaning Given protein meaning.
    * \return Return true if a given meaning is correct.
    */
    bool CheckProtein(std::string meaning);

    /*
    * \brief Check correctness of a given protein meaning.
    * \param meaning Given fat meaning.
    * \return Return true if a given meaning is correct.
    */
    bool CheckFat(std::string meaning);

    /*
    * \brief Check correctness of a given protein meaning.
    * \param meaning Given carbohydrate meaning.
    * \return Return true if a given meaning is correct.
    */
    bool CheckCarbo(std::string meaning);

private:
    //! Check if given string can be converted to flaot
    bool IsDigitF(std::string s);
};
#endif
