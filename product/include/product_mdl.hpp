#ifndef PRODUCT_MDL_HPP
#define PRODUCT_MDL_HPP
#include "product_ctrl_im.hpp"
#include "product.hpp"
#include <map>
#include <string>
#include <vector>
#include <algorithm>

class ProductMdl {
private:
    using ProductTbl = std::map<std::string, Product>;
    IMProductCtrl* controller_;
    ProductTbl products_;
public:
    enum class Parameter {protein, fet, carbohydrate};
    ProductMdl(IMProductCtrl* controller) :controller_(controller) {};
    ~ProductMdl();
    /*!
    * \brief Read products table.
    * \param name [in|out] Records to insert. Successfully inserted records are removed from parameter.
    */
    void Inititalize(std::vector<std::vector<std::string>>& records);

    /*!
    * \brief Add record to products table.
    * \param name Product name.
    * \param p Weight of protein in gramms per 100 grammm of product.
    * \param f Weight of fet in gramms per 100 grammm of product.
    * \param c Weight of carbohydrate in gramms per 100 grammm of product.
    * \return Return true if insertion of record was successful.
    */
    bool AddProduct(std::string name, float p, float f, float c);

    /*!
    * \brief Write to method parameters all records.
    * \params products [out] records with all products {name, protein, fet, carbohydrate}
    */
    void GetProducts(std::vector<std::vector<std::string>>& products);

    //! \brief Save data
    void Save();

    /*!
    * \brief Update product parameters.
    * \param name Name of product.
    * \param parameter Parameter to update.
    * \param meaning New value of parameter.
    * \return returns true if update was successful.
    */
    bool UpdateProduct(std::string name, Parameter parameter, float meaning);

    /*!
    * \brief Delete product.
    * \param name Name of product to delete.
    * \return returns true if product was deleted.
    */
    bool DeleteProduct(std::string name);

    /*!
      * \brief Get product by name.
      * \param name Name of product to get.
      * \return returns const pointer to product; nullptr - if no product with this name was found.
    */
    const Product* GetProduct(std::string name);
};
#endif
