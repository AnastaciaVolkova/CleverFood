#include "product/product_mdl.hpp"

using std::to_string;
using std::vector;
using std::string;
using std::stof;

ProductMdl::~ProductMdl() {
    if (to_save_.size() != 0) {
        vector<vector<string>> records;
        for (auto s : to_save_) {
            auto it = products_.find(Product(s, 0, 0, 0));
            records.push_back({ it->GetName(), to_string(it->GetProteinGr()), to_string(it->GetFatGr()), to_string(it->GetCarbGr()) });
        }
        controller_->Store(records);
    }
};

bool ProductMdl::AddProduct(string name, float p, float f, float c, bool is_ini) {
    auto pr = products_.emplace(name, p, f, c);
    if ((pr.second) && (!is_ini))
        to_save_.push_back(name);
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

void ProductMdl::ClearSave() { to_save_.clear(); };

void ProductMdl::Save() {
    if (to_save_.size() != 0) {
        vector<vector<string>> records;
        for (auto s : to_save_) {
            auto it = products_.find(Product(s, 0, 0, 0));
            records.push_back({ it->GetName(), to_string(it->GetProteinGr()), to_string(it->GetFatGr()), to_string(it->GetCarbGr()) });
        }
        controller_->Store(records);
    }
}