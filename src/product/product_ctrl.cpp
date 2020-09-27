#include "product/product_ctrl.hpp"
#ifndef QT_VERSION
#include "view.hpp"
#endif

#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

ProductCtrl::ProductCtrl(string file) {
    model_ = std::make_unique<ProductMdl>(this);
    ifstream ifs(file);
    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        vector<string> tokens(std::istream_iterator<string>{iss}, std::istream_iterator<string>());
        if (tokens.size() == 4)
            model_->AddProduct(tokens[0], stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
    }
    ifs.close();
};

void ProductCtrl::SetView(ProductView* view) { view_ = view; };

void ProductCtrl::Show() {
    vector<vector<string>> records;
    model_->GetProducts(records);
    view_->Show(records);
};

bool ProductCtrl::AddProduct(std::string name, float p, float f, float c) {
    return model_->AddProduct(name, p, f, c);
};