#ifndef PRODUCT_MDL_HPP
#define PRODUCT_MDL_HPP
#include "product/product_ctrl_im.hpp"
#include "product/product.hpp"
#include <set>
#include <string>
#include <vector>

class ProductMdl {
private:
    using ProductTbl = std::set<Product>;
    IMProductCtrl* controller_;
    ProductTbl products_;
public:
    ProductMdl(IMProductCtrl* controller) :controller_(controller) {};
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
};
#endif
