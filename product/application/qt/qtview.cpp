#include "qtview.h"
#include "ui_qtview.h"
#include "product_ctrl.hpp"
#include "storage_text.hpp"
#include <vector>
#include <QString>
#include <string>

using std::make_unique;
using std::vector;
using std::string;

QTView::QTView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QTView)
{
    ui->setupUi(this);
    controller_ = make_unique<ProductCtrl>(
                make_unique<StorageText>("../../../../data/products.txt"));
    controller_->SetView(this);
}

void QTView::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    controller_->Show();
};

QTView::~QTView()
{
    delete ui;
}

void QTView::Show(std::vector<std::vector<std::string>> records) {
    ui->productTable->setColumnCount(records[0].size());
    ui->productTable->setRowCount(records.size());
    ui->productTable->setHorizontalHeaderLabels(QStringList({"Product", "Proteins", "Fats", "Carbohydrates"}));

    for (size_t r = 0; r < records.size(); r++){
        string product_name = records[r][0];
        if (cells_.find(product_name) == cells_.end()){
            vector<std::unique_ptr<QTableWidgetItem>> row_w;
            for (size_t c = 0; c < records[0].size(); c++)
                row_w.push_back(std::make_unique<QTableWidgetItem>(QString(records[r][c].c_str())));
            cells_.emplace(make_pair(product_name, row_w));
        } else {
            for (size_t c = 0; c < records[0].size(); c++)
                cells_[product_name][c]->setText(QString(records[r][c].c_str()));
        }
    }

    for (int r = 0; r < ui->productTable->rowCount(); r++){
        for (int c = 0; c < ui->productTable->columnCount(); c++)
            ui->productTable->setItem(r, c, cells_[records[r][0]][c].get());
    }
};
