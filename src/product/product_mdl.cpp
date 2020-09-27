#include "product/product_mdl.hpp"

bool ProductMdl::AddProduct(std::string name, float p, float f, float c) {
    auto pr = products_.emplace(name, p, f, c);
    return pr.second;
};
