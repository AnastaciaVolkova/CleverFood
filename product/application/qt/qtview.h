#ifndef QTVIEW_H
#define QTVIEW_H

#include <QWidget>
#include <QKeyEvent>
#include <memory>
#include <QTableWidgetItem>
#include "product_view_i.hpp"
#include "product_ctrl_iv.hpp"
#include <unordered_map>


QT_BEGIN_NAMESPACE
namespace Ui { class QTView; }
QT_END_NAMESPACE

class QTView;

class QTView : public QWidget, IProductView
{
    Q_OBJECT

public:
    QTView(QWidget *parent = nullptr);
    ~QTView();
    virtual void Show(std::vector<std::vector<std::string>> records) override;
    virtual void Run()override{};
protected:
    void showEvent(QShowEvent *event) override;
private slots:
    void on_product_tbl_cellChanged(int row, int column);

    void on_product_tbl_cellDoubleClicked(int row, int column);

    void on_save_btn_pressed();

    void on_product_tbl_itemSelectionChanged();

private:
    Ui::QTView *ui;
    std::unique_ptr<IVProductCtrl> controller_;
    std::unordered_map<std::string, std::vector<std::unique_ptr<QTableWidgetItem>>> cells_;
    void AddNewRow();
    std::vector<std::unique_ptr<QTableWidgetItem>> row_to_add_;
    int prev_row_;
};
#endif // QTVIEW_H
