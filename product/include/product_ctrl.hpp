#ifndef PRODUCT_CTRL_HPP_
#define PRODUCT_CTRL_HPP_
#include "product_mdl.hpp"
#include "product_ctrl_iv.hpp"
#include "product_ctrl_im.hpp"
#include "product_view_i.hpp"
#include "storage_i.hpp"
#include <memory>
#include <string>

class ProductView;

class ProductCtrl :public IMProductCtrl, public IVProductCtrl{
private:
    IProductView* view_;
    std::unique_ptr<ProductMdl> model_;
    std::unique_ptr<StorageI> storage_;
public:
    ProductCtrl(std::unique_ptr<StorageI> storage);
    /*!
    * \brief Set view for controller.
    * \param view Pointer to view. This view will be manipulated by controller.
    */
    void SetView(IProductView* view) override;

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
    bool AddProduct(std::string name, std::string p, std::string f, std::string c);

    /*!
    * \brief Update product in products base.
    * \param name Product name to update.
    * \param parameter Parameter to update.
    * \param meaning New meaning of parameter.
    * \return true if update was sucessfull.
    */
    bool UpdateProduct(std::string name, Parameter parameter, std::string meaning);

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
    bool CheckName() override;

    /*
    * \brief Check correctness of a given protein meaning.
    * \param meaning Given protein meaning.
    * \return Return true if a given meaning is correct.
    */
    bool CheckProtein() override;

    /*
    * \brief Check correctness of a given protein meaning.
    * \param meaning Given fat meaning.
    * \return Return true if a given meaning is correct.
    */
    bool CheckFat() override;

    /*
    * \brief Check correctness of a given protein meaning.
    * \param meaning Given carbohydrate meaning.
    * \return Return true if a given meaning is correct.
    */
    bool CheckCarbo() override;

    /*
     * \brief Enter to Add State.
     */
    virtual void GoToAddState() override;

    /*
     *  \brief Go to update state.
     */
    virtual void GoToUpdateState(std::string name, std::string protein, std::string fat, std::string carbo) override;

    /*
     * \brief Check if entered data are valid.
     * \return true if all entered data are valid.
     */
    virtual bool AnyError() override;

    /*
    *  \brief Enter product.
    *  \return true if product was entered successfully.
    */
    virtual bool SendAddProductRequest() override;

    /*
    *  \brief Send request to update product.
    *  \return true if product was updated successfully.
    */
    virtual bool SendUpdateProductRequest() override;

private:
    //! Check if given string can be converted to float.
    bool IsDigitF(std::string s);

    //! Check if record is valid for adding or updating.
    bool RecordIsReady();
};
#endif
