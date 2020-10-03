#include "product/product_ctrl.hpp"

#ifndef QT_VERSION
#include "view.hpp"
#endif

#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;
using std::string;
using std::unique_ptr;
using std::move;
using std::transform;


ProductCtrl::ProductCtrl(unique_ptr<StorageI> storage, string file) :store_filename_(file), storage_(move(storage)) {
    model_ = std::make_unique<ProductMdl>(this);
    ifstream ifs(store_filename_);
    string line;
    vector<vector<string>> records;
    while (getline(ifs, line)) {
        istringstream iss(line);
        vector<string> tokens(std::istream_iterator<string>{iss}, std::istream_iterator<string>());
        records.push_back(tokens);
    }
    ifs.close();
    model_->Inititalize(records);
};

void ProductCtrl::SetView(ProductView* view) { view_ = view; };

void ProductCtrl::Show() {
    vector<vector<string>> records;
    model_->GetProducts(records);
    view_->Show(records);
};

bool ProductCtrl::AddProduct(std::string name, float p, float f, float c) {
    std::transform(name.begin(), name.end(), name.begin(), std::tolower);
    return model_->AddProduct(name, p, f, c);
};

void ProductCtrl::Store(std::vector<std::vector<std::string>>& records) {
    if (records.size() != 0) {
        ofstream ofs(store_filename_);
        for (auto record : records) {
            string record_ln = "";
            for (string field : record)
                record_ln += field + " ";
            record_ln.erase(record_ln.size() - 1);
            ofs << record_ln << "\n";
        };
        ofs.close();
    }
};

void ProductCtrl::Save() {
    model_->Save();
};



bool ProductCtrl::UpdateProduct(std::string name, Parameter parameter, std::string meaning) {
    ProductMdl::Parameter param_m;
    switch (parameter) {
    case Parameter::protein: param_m = ProductMdl::Parameter::protein; break;
    case Parameter::fet: param_m = ProductMdl::Parameter::fet; break;
    case Parameter::carbohydrate: param_m = ProductMdl::Parameter::carbohydrate; break;
    default:return false;
    }
    return model_->UpdateProduct(name, param_m, stof(meaning));
};

bool ProductCtrl::DeleteProduct(std::string name) {
    return model_->DeleteProduct(name);
};
