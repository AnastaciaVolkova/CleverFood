#include "product/product_ctrl.hpp"
#ifndef QT_VERSION
#include "view.hpp"
#endif

#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

ProductCtrl::ProductCtrl(string file) :store_filename_(file) {
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
    return model_->AddProduct(name, p, f, c);
};

void ProductCtrl::Store(std::vector<std::vector<std::string>>& records) {
    if (records.size() != 0) {
        ofstream ofs(store_filename_, std::ios_base::app);
        for (auto record : records) {
            string record_ln = "";
            for (string field : record)
                record_ln += field + " ";
            record_ln.erase(record_ln.size() - 1);
            ofs << record_ln << "\n";
        };
        model_->ClearSave();
        ofs.close();
    }
};