#include "product_ctrl.hpp"

#ifndef QT_VERSION
#include "../application/console/product_main.hpp"
#endif

#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <regex>
#include <algorithm>
#include "context.hpp"

using std::string;
using std::vector;
using std::unique_ptr;
using std::move;
using std::transform;
using std::count;
using std::regex;
using std::smatch;

#define DEBUG_INFO


ProductCtrl::ProductCtrl(unique_ptr<StorageI> storage) : storage_(move(storage)) {
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

bool ProductCtrl::CheckName(std::string name) {
    regex re("^[a-z,A-Z]+.+");
    smatch sm;
    bool f = std::regex_match(name, sm, re);
    return f;
};

bool ProductCtrl::CheckProtein(std::string meaning) { return IsDigitF(meaning); };

bool ProductCtrl::CheckFat(std::string meaning) { return IsDigitF(meaning); };

bool ProductCtrl::CheckCarbo(std::string meaning) { return IsDigitF(meaning); };

bool ProductCtrl::IsDigitF(std::string s) {
    size_t n = count_if(s.begin(), s.end(), [](char a) {return (a == ',') || (a == '.'); });
    if (n >= 2)
        return false;
    auto it = s.begin();
    while ((it != s.end()) && ((*it == '.') | (*it == ',') | (isdigit(*it)))) { it++; };
    return it == s.end();
};

void ProductCtrl::EnterAdd() {
#if defined(DEBUG_INFO)
    std::cout << "EnterAdd <-" << context_.PrintCurrentState() << " ";
#endif
    context_.HandleLastRowGo();
#if defined(DEBUG_INFO)
    std::cout << "->" << context_.PrintCurrentState() << std::endl;
#endif
};

bool ProductCtrl::IsReadyToAdd() {return context_.Ready();};

bool ProductCtrl::AllOK(){return context_.AllOK();};

bool ProductCtrl::EnterName(std::string n){
#if defined(DEBUG_INFO)
    std::cout << "EnterName <-" << context_.PrintCurrentState() << " ";
#endif
    bool is_ok = ProductCtrl::CheckName(n);
    if (is_ok){
        context_.fields_[Context::Fields::kName] = n;
        context_.HandleVEnter();
    }
    else{
        context_.fields_[Context::Fields::kName] = "";
        context_.HandleInvEnter();
    }
#if defined(DEBUG_INFO)
    std::cout << "->" << context_.PrintCurrentState() << std::endl;
#endif
    return is_ok;
};

bool ProductCtrl::EnterProtein(std::string p){
#if defined(DEBUG_INFO)
    std::cout << "Enter Protein <-" << context_.PrintCurrentState() << " ";
#endif
    bool is_ok = ProductCtrl::CheckProtein(p);
    if (is_ok){
        context_.fields_[Context::Fields::kProtein] = p;
        context_.HandleVEnter();
    }
    else{
        context_.fields_[Context::Fields::kProtein] = "";
        context_.HandleInvEnter();
    }
#if defined(DEBUG_INFO)
    std::cout << "->" << context_.PrintCurrentState() << std::endl;
#endif
    return is_ok;
};

bool ProductCtrl::EnterFat(std::string f) {
#if defined(DEBUG_INFO)
    std::cout << "Enter Fat <-" << context_.PrintCurrentState() << " ";
#endif
    bool is_ok = ProductCtrl::CheckFat(f);
    if (is_ok){
        context_.fields_[Context::Fields::kFat] = f;
        context_.HandleVEnter();
    }
    else{
        context_.fields_[Context::Fields::kFat] = "";
        context_.HandleInvEnter();
    }
#if defined(DEBUG_INFO)
    std::cout << "->" << context_.PrintCurrentState() << std::endl;
#endif
    return is_ok;
};

bool ProductCtrl::EnterCarbo(std::string c){
#if defined(DEBUG_INFO)
    std::cout << "Enter Carbo <-" << context_.PrintCurrentState() << " ";
#endif
    bool is_ok = ProductCtrl::CheckCarbo(c);
    if (is_ok){
        context_.fields_[Context::Fields::kCarb] = c;
        context_.HandleVEnter();
    }
    else{
        context_.fields_[Context::Fields::kCarb] = "";
        context_.HandleInvEnter();
    }
#if defined(DEBUG_INFO)
    std::cout << "->" << context_.PrintCurrentState() << std::endl;
#endif
    return is_ok;
};

bool ProductCtrl::EnterProduct(){
#if defined(DEBUG_INFO)
    std::cout << "Enter product <-" << context_.PrintCurrentState() << " ";
#endif
    context_.HandleAddPressed();
#if defined(DEBUG_INFO)
    std::cout << "<-" << context_.PrintCurrentState() << std::endl;
#endif
    if (IsReadyToAdd())
        return AddProduct(context_.fields_[Context::Fields::kName],
                          context_.fields_[Context::Fields::kProtein],
                          context_.fields_[Context::Fields::kFat],
                          context_.fields_[Context::Fields::kCarb]);
    else
        return false;
};
