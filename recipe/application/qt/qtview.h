#ifndef QTVIEW_H
#define QTVIEW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class QTView; }
QT_END_NAMESPACE

class QTView : public QMainWindow
{
    Q_OBJECT

public:
    QTView(QWidget *parent = nullptr);
    ~QTView();
    void onSelectionChanged(const QItemSelection &selected);

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_pushButton_pressed();

private:
    Ui::QTView *ui;
    QSqlQueryModel* model_recipes_;
    QSqlRelationalTableModel* model_ingredients_;
    QItemSelectionModel* recipes_selection_model_;
    QSqlDatabase db;
};
#endif // QTVIEW_H
