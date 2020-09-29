#include "product/product_mdl.hpp"

using std::to_string;
using std::vector;
using std::string;
using std::stof;
using std::make_pair;

ProductMdl::~ProductMdl() {
    Save();
};

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
        products.push_back({ record.second.GetName(),
            to_string(record.second.GetProteinGr()),
            to_string(record.second.GetFatGr()),
            to_string(record.second.GetCarbGr()) });
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
    return true;
};