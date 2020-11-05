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
    virtual std::string GetName() override;
    virtual std::string GetProtein() override;
    virtual std::string GetFat() override;
    virtual std::string GetCarbo() override;
protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_product_tbl_cellChanged(int row, int column);

    void on_save_btn_pressed();

    void on_product_tbl_itemSelectionChanged();

    void on_delete_btn_pressed();

private:
    Ui::QTView *ui;
    std::unique_ptr<IVProductCtrl> controller_;
    void AddNewRow();
    int prev_row_;
};
#endif // QTVIEW_H
