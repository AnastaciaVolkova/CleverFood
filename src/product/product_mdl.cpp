#include "product/product_mdl.hpp"

using std::to_string;
using std::vector;
using std::string;
using std::stof;

ProductMdl::~ProductMdl() {
    Save();
};

bool ProductMdl::AddProduct(string name, float p, float f, float c, bool is_ini) {
    auto pr = products_.emplace(name, p, f, c);
    return pr.second;
};

void ProductMdl::Inititalize(vector<vector<string>>& records) {
    vector<vector<string>>::iterator it;
    vector<vector<vector<string>>::iterator> it_to_remove;
    for (it = records.begin(); it != records.end(); it++) {
        if (AddProduct((*it)[0], stof((*it)[1]), stof((*it)[2]), stof((*it)[3]), true))
            it_to_remove.push_back(it);
    }
    for (auto it_r = it_to_remove.rbegin(); it_r != it_to_remove.rend(); it_r++) {
        records.erase(*it_r);
    }
};

void ProductMdl::GetProducts(vector<vector<string>>& products) {
    products.clear();
    for (auto record : products_) {
        products.push_back({ record.GetName(),
            to_string(record.GetProteinGr()),
            to_string(record.GetFatGr()),
            to_string(record.GetCarbGr()) });
    }
};

void ProductMdl::Save() {
    vector<vector<string>> records;
    for (auto s : products_) {
        records.push_back({ s.GetName(), to_string(s.GetProteinGr()), to_string(s.GetFatGr()), to_string(s.GetCarbGr()) });
    }
    controller_->Store(records);
}
