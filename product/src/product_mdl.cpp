#include "product_mdl.hpp"
#include <iomanip>
#include <sstream>

using std::to_string;
using std::vector;
using std::string;
using std::stof;
using std::make_pair;
using std::fixed;
using std::setprecision;
using std::istringstream;
using std::ostringstream;


ProductMdl::~ProductMdl() {};

bool ProductMdl::AddProduct(string name, float p, float f, float c) {
    auto pr = products_.emplace(make_pair(name, Product(name, p, f, c)));
    return pr.second;
};

void ProductMdl::Inititalize(vector<vector<string>>& records) {
    vector<vector<string>>::iterator it;
    vector<vector<vector<string>>::iterator> it_to_remove;
    for (it = records.begin(); it != records.end(); it++) {
        if (AddProduct((*it)[0], stof((*it)[1]), stof((*it)[2]), stof((*it)[3])))
            it_to_remove.push_back(it);
    }
    for (auto it_r = it_to_remove.rbegin(); it_r != it_to_remove.rend(); it_r++) {
        records.erase(*it_r);
    }
};

void ProductMdl::GetProducts(vector<vector<string>>& products) {
    products.clear();
    for (auto record : products_) {
        string p, f, c;
        ostringstream oss;
        oss << fixed << setprecision(2) << record.second.GetProteinGr();
        p = oss.str();

        oss.str("");
        oss << fixed << setprecision(2) << record.second.GetFatGr();
        f = oss.str();

        oss.str("");
        oss << fixed << setprecision(2) << record.second.GetCarbGr();
        c = oss.str();

        products.push_back({ record.second.GetName(), p, f, c });
    }
};

void ProductMdl::Save() {
    vector<vector<string>> records;
    for (auto s : products_) {
        records.push_back({
            s.second.GetName(),
            to_string(s.second.GetProteinGr()),
            to_string(s.second.GetFatGr()),
            to_string(s.second.GetCarbGr()) });
    }
    controller_->Store(records);
}

bool ProductMdl::UpdateProduct(std::string name, Parameter parameter, float meaning) {
    if (products_.find(name) == products_.end())
        return false;
    switch (parameter) {
    case Parameter::protein: products_[name].SetProteinGr(meaning); break;
    case Parameter::fet: products_[name].SetFatGr(meaning); break;
    case Parameter::carbohydrate: products_[name].SetCarbGr(meaning); break;
    default: return false;
    }
    return true;
};

bool ProductMdl::DeleteProduct(std::string name) {
    size_t n = products_.erase(name);
    return n != 0;
};

const Product* ProductMdl::GetProduct(std::string name){
    if (products_.find(name) == products_.end())
        return nullptr;
    else
        return &products_[name];
};
