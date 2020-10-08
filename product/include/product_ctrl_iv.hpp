#ifndef PRODUCT_CTRL_IV_HPP
#define PRODUCT_CTRL_IV_HPP

#include "product_view_i.hpp"
#include <memory>
#include <string>

class IVProductCtrl {
public:
    enum class Parameter{protein, fet, carbohydrate};
    virtual void SetView(IProductView* view) = 0;
    virtual void Show() = 0;
    virtual void Save() = 0;
    virtual bool AddProduct(std::string name, std::string p, std::string f, std::string c) = 0;
    virtual bool UpdateProduct(std::string name, Parameter parameter, std::string meaning) = 0;
    virtual bool DeleteProduct(std::string name) = 0;
    virtual bool CheckName(std::string name) = 0;
    virtual bool CheckProtein(std::string meaning) = 0;
    virtual bool CheckFat(std::string meaning) = 0;
    virtual bool CheckCarbo(std::string meaning) = 0;
    virtual ~IVProductCtrl() {};
};
#endif
