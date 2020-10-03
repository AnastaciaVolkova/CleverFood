#ifndef PRODUCT_CTRL_IV_HPP
#define PRODUCT_CTRL_IV_HPP

#include <memory>
#include <string>

class ProductView;

class IVProductCtrl {
public:
    enum class Parameter{protein, fet, carbohydrate};
    virtual void SetView(ProductView* view) = 0;
    virtual void Show() = 0;
    virtual void Save() = 0;
    virtual bool AddProduct(std::string name, float p, float f, float c) = 0;
    virtual bool UpdateProduct(std::string name, Parameter parameter, std::string meaning) = 0;
    virtual bool DeleteProduct(std::string name) = 0;
    virtual bool CheckName(std::string name) = 0;
    virtual bool CheckProtein(std::string meaning) = 0;
    virtual bool CheckFat(std::string meaning) = 0;
    virtual bool CheckCarbo(std::string meaning) = 0;
    virtual ~IVProductCtrl() {};
};
#endif
