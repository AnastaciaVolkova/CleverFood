#include "product/product_mdl.hpp"

using std::to_string;

bool ProductMdl::AddProduct(std::string name, float p, float f, float c) {
    auto pr = products_.emplace(name, p, f, c);
    return pr.second;
};

void ProductMdl::GetProducts(std::vector<std::vector<std::string>>& products) {
    products.clear();
    for (auto record : products_) {
        products.push_back({ record.GetName(),
            to_string(record.GetProteinGr()),
            to_string(record.GetFatGr()),
            to_string(record.GetCarbGr()) });
    }
};
