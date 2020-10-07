#include "product/product_ctrl.hpp"

#ifndef QT_VERSION
#include "product/test/product_main.hpp"
#endif

#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;
using std::string;
using std::unique_ptr;
using std::move;
using std::transform;
using std::count;


ProductCtrl::ProductCtrl(unique_ptr<StorageI> storage) : storage_(move(storage)) {
    model_ = std::make_unique<ProductMdl>(this);
    string line;
    vector<vector<string>> records;
    storage_->Open();
    storage_->Select(records);
    model_->Inititalize(records);
};

void ProductCtrl::SetView(ProductView* view) { view_ = view; };

void ProductCtrl::Show() {
    vector<vector<string>> records;
    model_->GetProducts(records);
    view_->Show(records);
};

bool ProductCtrl::AddProduct(std::string name, std::string p, std::string f, std::string c) {
    size_t pos;
    std::transform(name.begin(), name.end(), name.begin(), std::tolower);

    pos = p.find(',');
    if (pos != string::npos)
        p.replace(pos, 1, ".");

    pos = f.find(',');
    if (pos != string::npos)
        f.replace(pos, 1, ".");

    pos = c.find(',');
    if (pos != string::npos)
        c.replace(pos, 1, ".");

    return model_->AddProduct(name, stof(p), stof(f), stof(c));
};

void ProductCtrl::Store(std::vector<std::vector<std::string>>& records) {
    if (storage_.get() != nullptr)
        storage_->Save(records);
};

void ProductCtrl::Save() {
    model_->Save();
};

bool ProductCtrl::UpdateProduct(std::string name, Parameter parameter, std::string meaning) {
    ProductMdl::Parameter param_m;
    switch (parameter) {
    case Parameter::protein: param_m = ProductMdl::Parameter::protein; break;
    case Parameter::fet: param_m = ProductMdl::Parameter::fet; break;
    case Parameter::carbohydrate: param_m = ProductMdl::Parameter::carbohydrate; break;
    default:return false;
    }
    return model_->UpdateProduct(name, param_m, stof(meaning));
};

bool ProductCtrl::DeleteProduct(std::string name) {
    std::transform(name.begin(), name.end(), name.begin(), std::tolower);
    return model_->DeleteProduct(name);
};

bool ProductCtrl::CheckName(std::string name) { return true; };

bool ProductCtrl::CheckProtein(std::string meaning) { return IsDigitF(meaning); };

bool ProductCtrl::CheckFat(std::string meaning) { return IsDigitF(meaning); };

bool ProductCtrl::CheckCarbo(std::string meaning) { return IsDigitF(meaning); };

bool ProductCtrl::IsDigitF(std::string s) {
    //if (!isdigit(s[0]))
    //    return false;
    size_t n = count_if(s.begin(), s.end(), [](char a) {return (a == ',') || (a == '.'); });
    if (n >= 2)
        return false;
    auto it = s.begin();
    while ((it != s.end()) && ((*it == '.') | (*it == ',') | (isdigit(*it)))) { it++; };
    return it == s.end();
};
