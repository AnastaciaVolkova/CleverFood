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
    ui->verticalLayoutWidget->setGeometry(QRect(0,0,this->width(), this->height()));
    controller_->Show();
};

QTView::~QTView()
{
    delete ui;
}

void QTView::Show(std::vector<std::vector<std::string>> records) {
    ui->product_tbl->blockSignals(true);
    ui->product_tbl->setColumnCount(records[0].size());
    ui->product_tbl->setRowCount(records.size());
    ui->product_tbl->setHorizontalHeaderLabels(QStringList({"Product", "Proteins", "Fats", "Carbohydrates"}));

    for (int r = 0; r < ui->product_tbl->rowCount(); r++){
        for (int c = 0; c < ui->product_tbl->columnCount(); c++){
            ui->product_tbl->setItem(r, c, new QTableWidgetItem(QString(records[r][c].c_str())));
        }
    }

    AddNewRow();
    ui->product_tbl->blockSignals(false);
    prev_row_ = ui->product_tbl->currentRow();
};

void QTView::on_product_tbl_cellChanged(int row, int column)
{
    qInfo() << "Cell changed event";

    ui->product_tbl->blockSignals(true);

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
        if (!p->AnyError()){
            ui->status_lbl->setText("All OK");
            ui->status_lbl->setStyleSheet("QLabel{color:green}");
        }
        else{
                ui->status_lbl->setText("There are errors");
                ui->status_lbl->setStyleSheet("QLabel{color:red}");
        }
        ui->product_tbl->item(row, column)->setBackground(Qt::white);
    }
    ui->product_tbl->blockSignals(false);
}

void QTView::AddNewRow(){
    ui->product_tbl->blockSignals(true);
    ui->product_tbl->setRowCount(ui->product_tbl->rowCount()+1);

    for (int c = 0; c < ui->product_tbl->columnCount(); c++){
        ui->product_tbl->setItem(ui->product_tbl->rowCount()-1, c, new QTableWidgetItem(QString("")));
    }
    ui->product_tbl->blockSignals(false);
};

void QTView::on_save_btn_pressed()
{
    controller_->Save();
    ui->status_lbl->setText("Successfully saved");
    ui->status_lbl->setStyleSheet("QLabel{color:green}");
}

void QTView::on_product_tbl_itemSelectionChanged()
{
    int currentRow = ui->product_tbl->currentRow();
    if (currentRow == ui->product_tbl->rowCount()-1){
        ui->delete_btn->setEnabled(false);
        controller_->GoToAddState();
    } else{
        if (prev_row_ != currentRow){
            if (prev_row_ == ui->product_tbl->rowCount()-1){
                if (controller_->SendAddProductRequest()){
                    AddNewRow();
                    ui->status_lbl->setText("Successfully added");
                    ui->status_lbl->setStyleSheet("QLabel{color:green}");
                } else {
                    ui->status_lbl->setText("Item was not added");
                    ui->status_lbl->setStyleSheet("QLabel{color:red}");
                    ui->product_tbl->blockSignals(true);
                    for (int c = 0; c < ui->product_tbl->columnCount(); c++){
                        ui->product_tbl->item(prev_row_, c)->setText("");
                        ui->product_tbl->item(prev_row_, c)->setBackground(Qt::white);
                    }
                    ui->product_tbl->blockSignals(false);
                };
            }
            if (controller_->IsReadyToUpdate())
                controller_->SendUpdateProductRequest();
            controller_->GoToUpdateState(
                        ui->product_tbl->item(currentRow, 0)->text().toStdString(),
                        ui->product_tbl->item(currentRow, 1)->text().toStdString(),
                        ui->product_tbl->item(currentRow, 2)->text().toStdString(),
                        ui->product_tbl->item(currentRow, 3)->text().toStdString()
                        );
        }
        ui->delete_btn->setEnabled(true);
    }
    prev_row_ = currentRow;
}

void QTView::on_delete_btn_pressed()
{
    ui->product_tbl->blockSignals(true);
    int currentRow = ui->product_tbl->currentRow();
    if (currentRow != ui->product_tbl->rowCount()-1){
        std::string name = ui->product_tbl->item(currentRow, 0)->text().toStdString();
        if (controller_->DeleteProduct(name)){
            ui->status_lbl->setText("Successfully deleted");
            ui->status_lbl->setStyleSheet("QLabel{color:green}");
            ui->product_tbl->removeRow(currentRow);
        }
    }
    ui->product_tbl->blockSignals(false);
}

void QTView::closeEvent(QCloseEvent *event) {
    controller_->Save();
}

void QTView::resizeEvent(QResizeEvent *event) {
    ui->verticalLayoutWidget->setGeometry(QRect(0,0,this->width(), this->height()));
}

string QTView::GetNameToAdd() {
    return ui->product_tbl->item(ui->product_tbl->rowCount()-1, 0)->text().toStdString();
}

string QTView::GetProteinToAdd() {
    return ui->product_tbl->item(ui->product_tbl->rowCount()-1, 1)->text().toStdString();
}

string QTView::GetFatToAdd() {
    return ui->product_tbl->item(ui->product_tbl->rowCount()-1, 2)->text().toStdString();
}

string QTView::GetCarboToAdd() {
    return ui->product_tbl->item(ui->product_tbl->rowCount()-1, 3)->text().toStdString();
}
