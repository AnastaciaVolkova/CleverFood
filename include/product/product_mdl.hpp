#ifndef PRODUCT_MDL_HPP
#define PRODUCT_MDL_HPP
#include "product/product_ctrl_im.hpp"
#include "product/product.hpp"
#include <set>
#include <string>

class ProductMdl {
private:
    using ProductTbl = std::set<Product>;
    IMProductCtrl* controller_;
    ProductTbl products_;
public:
    ProductMdl(IMProductCtrl* controller) :controller_(controller) {};
    /*!
    * \brief Add record to products table.
    * \param name Product name.
    * \param p Weight of protein in gramms per 100 grammm of product.
    * \param f Weight of fet in gramms per 100 grammm of product.
    * \param c Weight of carbohydrate in gramms per 100 grammm of product.
    * \return Return true if insertion of record was successful.
    */
    bool AddProduct(std::string name, float p, float f, float c);
};
#endif
