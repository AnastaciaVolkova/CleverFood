#ifndef PRODUCT_MDL_HPP
#define PRODUCT_MDL_HPP
#include "product/product_ctrl_im.hpp"

class ProductMdl {
private:
    IMProductCtrl* controller_;
public:
    ProductMdl(IMProductCtrl* controller):controller_(controller) {};
};
#endif