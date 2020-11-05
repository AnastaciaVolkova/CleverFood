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

#if defined(DEBUG_INFO)
#if defined(QT_CORE_LIB)
#include <QDebug>
#define print_debug(x) qInfo() << QString::fromStdString(x)
#else
#define print_debug(x) std::cout << x << std::endl
#endif
#endif


ProductCtrl::ProductCtrl(unique_ptr<StorageI> storage) : storage_(move(storage)), context_(this) {
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

void ProductCtrl::GoToAddState() {
#if defined(DEBUG_INFO)
    std::string debug_info_str = "EnterAdd: " + context_.PrintCurrentState();
#endif
    context_.HandleAGo();
#if defined(DEBUG_INFO)
    debug_info_str += "->" + context_.PrintCurrentState();
    print_debug(debug_info_str);
#endif
};

void ProductCtrl::GoToUpdateState(std::string name, std::string protein, std::string fat, std::string carbo) {
#if defined(DEBUG_INFO)
    std::string debug_info_str = "StartToUpdate: " + context_.PrintCurrentState();
#endif
    context_.fields_[Context::Fields::kName] = name;
    context_.fields_[Context::Fields::kProtein] = protein;
    context_.fields_[Context::Fields::kFat] = fat;
    context_.fields_[Context::Fields::kCarb] = carbo;
    context_.HandleUDGo();
#if defined(DEBUG_INFO)
    debug_info_str += "->" + context_.PrintCurrentState();
    print_debug(debug_info_str);
#endif
};

bool ProductCtrl::IsReadyToAdd() {
    bool is_ready_to_add = true;
    is_ready_to_add &= CheckName(view_->GetName());
    is_ready_to_add &= CheckProtein(view_->GetProtein());
    is_ready_to_add &= CheckFat(view_->GetFat());
    is_ready_to_add &= CheckCarbo(view_->GetCarbo());
    return is_ready_to_add;
};

bool ProductCtrl::IsReadyToUpdate() {return context_.ReadyToUpdate();};

bool ProductCtrl::AnyError(){
    bool any_error = false;
    any_error |= !CheckName(view_->GetName()) && view_->GetName()!="";
    any_error |= !CheckProtein(view_->GetProtein()) && view_->GetProtein() != "";
    any_error |= !CheckFat(view_->GetFat()) && view_->GetFat() != "";
    any_error |= !CheckCarbo(view_->GetCarbo()) && view_->GetCarbo() != "";
    return any_error;
};

bool ProductCtrl::EnterName(std::string n){
#if defined(DEBUG_INFO)
    std::string debug_info_str = "EnterName: " + context_.PrintCurrentState();
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
    debug_info_str += "->" + context_.PrintCurrentState();
    print_debug(debug_info_str);
#endif
    return is_ok;
};

bool ProductCtrl::EnterProtein(std::string p){
#if defined(DEBUG_INFO)
    std::string debug_info_str = "EnterProtein: " + context_.PrintCurrentState();
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
    debug_info_str += "->" + context_.PrintCurrentState();
    print_debug(debug_info_str);
#endif
    return is_ok;
};

bool ProductCtrl::EnterFat(std::string f) {
#if defined(DEBUG_INFO)
    std::string debug_info_str = "EnterFat: " + context_.PrintCurrentState();
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
    debug_info_str += "->" + context_.PrintCurrentState();
    print_debug(debug_info_str);
#endif
    return is_ok;
};

bool ProductCtrl::EnterCarbo(std::string c){
#if defined(DEBUG_INFO)
    std::string debug_info_str = "EnterCarbo: " + context_.PrintCurrentState();
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
    debug_info_str += "->" + context_.PrintCurrentState();
    print_debug(debug_info_str);
#endif
    return is_ok;
};

bool ProductCtrl::SendAddProductRequest(){
#if defined(DEBUG_INFO)
    std::string debug_info_str = "EnterProduct: " + context_.PrintCurrentState();
#endif
    if (IsReadyToAdd()){
        context_.HandleAddRequest();
#if defined(DEBUG_INFO)
        debug_info_str += "->" + context_.PrintCurrentState();
        print_debug(debug_info_str);
#endif
        return AddProduct(view_->GetName(),
                          view_->GetProtein(),
                          view_->GetFat(),
                          view_->GetCarbo());
    }
    else{
#if defined(DEBUG_INFO)
        debug_info_str += "->" + context_.PrintCurrentState();
        print_debug(debug_info_str);
#endif
        return false;
    }
};

bool ProductCtrl::SendUpdateProductRequest() {
#if defined(DEBUG_INFO)
    std::string debug_info_str = "SendUpdateProductRequest: " + context_.PrintCurrentState();
#endif
    context_.HandleAddRequest();
#if defined(DEBUG_INFO)
    debug_info_str += "->" + context_.PrintCurrentState();
    print_debug(debug_info_str);
#endif
    const Product* product = model_->GetProduct(context_.fields_[Context::Fields::kName]);
    if (IsReadyToAdd()){
        float meaning;
        meaning = stof(context_.fields_[Context::Fields::kProtein]);
        if (product->GetProteinGr() != meaning)
            model_->UpdateProduct(product->GetName(), ProductMdl::Parameter::protein, meaning);

        meaning = stof(context_.fields_[Context::Fields::kFat]);
        if (product->GetFatGr() != meaning)
            model_->UpdateProduct(product->GetName(), ProductMdl::Parameter::fet, meaning);

        meaning = stof(context_.fields_[Context::Fields::kCarb]);
        if (product->GetCarbGr() != meaning)
            model_->UpdateProduct(product->GetName(), ProductMdl::Parameter::carbohydrate, meaning);
        context_.fields_.clear();
        return true;
    }
    else
        return false;
};
