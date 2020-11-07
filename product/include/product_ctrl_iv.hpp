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
    virtual bool DeleteProduct(std::string name) = 0;
    virtual bool CheckName() = 0;
    virtual bool CheckProtein() = 0;
    virtual bool CheckFat() = 0;
    virtual bool CheckCarbo() = 0;
    virtual void GoToAddState() = 0;
    virtual void GoToUpdateState(std::string name, std::string protein, std::string fat, std::string carbo) = 0;
    virtual bool AnyError() = 0;
    virtual ~IVProductCtrl() {};
    virtual bool SendAddProductRequest() = 0;
    virtual bool SendUpdateProductRequest() = 0;
};
#endif
