#include "product_ctrl.hpp"

#ifndef QT_CORE_LIB
#include "../application/console/product_main.hpp"
#endif

#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <regex>
#include <algorithm>

using std::string;
using std::vector;
using std::unique_ptr;
using std::move;
using std::transform;
using std::count;
using std::regex;
using std::smatch;

#define DEBUG_INFO

#if defined(DEBUG_INFO)
#if defined(QT_CORE_LIB)
#include <QDebug>
#define print_debug(x) qInfo() << QString::fromStdString(x)
#else
#define print_debug(x) std::cout << x << std::endl
#endif
#endif


ProductCtrl::ProductCtrl(unique_ptr<StorageI> storage) : storage_(move(storage)){
    model_ = std::make_unique<ProductMdl>(this);
    string line;
    vector<vector<string>> records;
    storage_->Open();
    storage_->Select(records);
    model_->Inititalize(records);
};

void ProductCtrl::SetView(IProductView* view) { view_ = view; };

void ProductCtrl::Show() {
    vector<vector<string>> records;
    model_->GetProducts(records);
    view_->Show(records);
};

bool ProductCtrl::AddProduct(std::string name, std::string p, std::string f, std::string c) {
    size_t pos;
    transform(name.begin(), name.end(), name.begin(), ::tolower);

    pos = p.find(',');
    if (pos != string::npos)
        p.replace(pos, 1, ".");
    if (!IsDigitF(p))
        return false;

    pos = f.find(',');
    if (pos != string::npos)
        f.replace(pos, 1, ".");
    if (!IsDigitF(f))
        return false;

    pos = c.find(',');
    if (pos != string::npos)
        c.replace(pos, 1, ".");
    if (!IsDigitF(c))
        return false;

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
    if (((parameter == Parameter::protein) || (parameter == Parameter::fet) || (parameter == Parameter::carbohydrate))
        && (!IsDigitF(meaning)))
        return false;

    switch (parameter) {
    case Parameter::protein: param_m = ProductMdl::Parameter::protein; break;
    case Parameter::fet: param_m = ProductMdl::Parameter::fet; break;
    case Parameter::carbohydrate: param_m = ProductMdl::Parameter::carbohydrate; break;
    default:return false;
    }
    size_t pos = meaning.find(',');
    if (pos != string::npos)
        meaning.replace(pos, 1, ".");

    return model_->UpdateProduct(name, param_m, stof(meaning));
};

bool ProductCtrl::DeleteProduct(std::string name) {
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    return model_->DeleteProduct(name);
};

bool ProductCtrl::CheckName() {
    regex re("^[a-z,A-Z]+.+");
    smatch sm;
    string name = view_->GetName();
    bool f = std::regex_match(name, sm, re);
    return f;
};

bool ProductCtrl::CheckProtein() {
    return IsDigitF(view_->GetProtein());
};

bool ProductCtrl::CheckFat() {
    return IsDigitF(view_->GetFat());
};

bool ProductCtrl::CheckCarbo() {
    return IsDigitF(view_->GetCarbo());
};

bool ProductCtrl::IsDigitF(std::string s) {
    size_t n = count_if(s.begin(), s.end(), [](char a) {return (a == ',') || (a == '.'); });
    if ((n >= 2) || (s==""))
        return false;
    auto it = s.begin();
    while ((it != s.end()) && ((*it == '.') | (*it == ',') | (isdigit(*it)))) { it++; };
    return it == s.end();
};

void ProductCtrl::GoToAddState() {
};

void ProductCtrl::GoToUpdateState(std::string name, std::string protein, std::string fat, std::string carbo) {
};

bool ProductCtrl::RecordIsReady() {
    bool is_ready_to_add = true;
    is_ready_to_add &= CheckName();
    is_ready_to_add &= CheckProtein();
    is_ready_to_add &= CheckFat();
    is_ready_to_add &= CheckCarbo();
    return is_ready_to_add;
};

bool ProductCtrl::AnyError(){
    bool any_error = false;
    any_error |= !CheckName() && view_->GetName()!="";
    any_error |= !CheckProtein() && view_->GetProtein() != "";
    any_error |= !CheckFat() && view_->GetFat() != "";
    any_error |= !CheckCarbo() && view_->GetCarbo() != "";
    return any_error;
};

bool ProductCtrl::SendAddProductRequest(){
    if (RecordIsReady()){
        return AddProduct(view_->GetName(),
                          view_->GetProtein(),
                          view_->GetFat(),
                          view_->GetCarbo());
    }
    else{
        return false;
    }
};

bool ProductCtrl::SendUpdateProductRequest() {
    if (RecordIsReady()){
        float meaning;
        const Product* product = model_->GetProduct(view_->GetName());
        meaning = stof(view_->GetProtein());
        if (product->GetProteinGr() != meaning)
            model_->UpdateProduct(product->GetName(), ProductMdl::Parameter::protein, meaning);

        meaning = stof(view_->GetFat());
        if (product->GetFatGr() != meaning)
            model_->UpdateProduct(product->GetName(), ProductMdl::Parameter::fet, meaning);

        meaning = stof(view_->GetCarbo());
        if (product->GetCarbGr() != meaning)
            model_->UpdateProduct(product->GetName(), ProductMdl::Parameter::carbohydrate, meaning);
        return true;
    }
    else
        return false;
};
