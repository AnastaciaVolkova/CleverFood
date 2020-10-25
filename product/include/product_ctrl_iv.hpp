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
    virtual void GoToAddState() = 0;
    virtual void GoToUpdateState(std::string name, std::string protein, std::string fat, std::string carbo) = 0;
    virtual bool IsReadyToAdd() = 0;
    virtual bool IsReadyToUpdate() = 0;
    virtual bool AllOK() = 0;
    virtual ~IVProductCtrl() {};
    virtual bool EnterName(std::string n) = 0;
    virtual bool EnterProtein(std::string p) = 0;
    virtual bool EnterFat(std::string f) = 0;
    virtual bool EnterCarbo(std::string c) = 0;
    virtual bool EnterProduct() = 0;
    virtual bool SendUpdateProductRequest() = 0;
};
#endif
