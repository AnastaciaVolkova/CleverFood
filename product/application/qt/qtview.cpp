#include "qtview.h"
#include "ui_qtview.h"
#include "product_ctrl.hpp"
#include "storage_text.hpp"
#include <vector>
#include <QString>
#include <string>
#include <QDebug>


using std::make_unique;
using std::make_pair;
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
    ui->product_tbl->blockSignals(true);
    ui->product_tbl->setColumnCount(records[0].size());
    ui->product_tbl->setRowCount(records.size()+1);
    ui->product_tbl->setHorizontalHeaderLabels(QStringList({"Product", "Proteins", "Fats", "Carbohydrates"}));

    for (size_t r = 0; r < records.size(); r++){
        string product_name = records[r][0];
        if (cells_.find(product_name) == cells_.end()){
            vector<std::unique_ptr<QTableWidgetItem>> row_w;
            for (size_t c = 0; c < records[0].size(); c++)
                row_w.push_back(std::make_unique<QTableWidgetItem>(QString(records[r][c].c_str())));
            cells_.emplace(make_pair(product_name, std::move(row_w)));
        } else {
            for (size_t c = 0; c < records[0].size(); c++)
                cells_[product_name][c]->setText(QString(records[r][c].c_str()));
        }
    }

    for (int r = 0; r < ui->product_tbl->rowCount()-1; r++){
        for (int c = 0; c < ui->product_tbl->columnCount(); c++)
            ui->product_tbl->setItem(r, c, cells_[records[r][0]][c].get());
    }

    vector<std::unique_ptr<QTableWidgetItem>> row;
    for (int c = 0; c < ui->product_tbl->columnCount(); c++)
        row.push_back(std::make_unique<QTableWidgetItem>(QString("")));

    if (cells_.find("") == cells_.end()){
        cells_.emplace(make_pair("", std::move(row)));
    }

    for (int c = 0; c < ui->product_tbl->columnCount(); c++){
        ui->product_tbl->setItem(ui->product_tbl->rowCount()-1, c, cells_[""][c].get());
    }
    ui->product_tbl->blockSignals(false);
};

void QTView::on_product_tbl_cellChanged(int row, int column)
{
    if (cells_.find("") != cells_.end()){
        if (row == ui->product_tbl->rowCount()-1){
                std::string meaning = ui->product_tbl->item(row, column)->text().toStdString();
                std::vector<bool(IVProductCtrl::*)(std::string)> v{
                    &IVProductCtrl::EnterName,
                    &IVProductCtrl::EnterProtein,
                    &IVProductCtrl::EnterFat,
                    &IVProductCtrl::EnterCarbo,
                };
                IVProductCtrl* p = controller_.get();
                std::string s = ui->product_tbl->item(row, column)->text().toStdString();
                if (!(p->*v[column])(s)){
                    ui->product_tbl->item(row, column)->setBackground(Qt::red);
                    ui->status_lbl->setText("Invalid value");
                    ui->status_lbl->setStyleSheet("QLabel{color:red}");
                }
                else{
                    if (p->AllOK()){
                        ui->status_lbl->setText("All OK");
                        ui->status_lbl->setStyleSheet("QLabel{color:green}");
                    }
                    else{
                        ui->status_lbl->setText("There are errors");
                        ui->status_lbl->setStyleSheet("QLabel{color:red}");}
                    ui->product_tbl->item(row, column)->setBackground(Qt::white);
                }
                if (controller_->IsReadyToAdd())
                    ui->add_btn->setEnabled(true);
                else
                    ui->add_btn->setEnabled(false);
            };
        }
}

void QTView::on_product_tbl_cellDoubleClicked(int row, int column)
{
    if (row == ui->product_tbl->rowCount()-1){
        controller_->EnterAdd();
    }
}

void QTView::on_add_btn_pressed()
{
    if (controller_->EnterProduct()){
        ui->status_lbl->setText("Successfully added");
        ui->status_lbl->setStyleSheet("QLabel{color:green}");
    } else {
        ui->status_lbl->setText("Product was not added");
        ui->status_lbl->setStyleSheet("QLabel{color:red}");
    };
}
