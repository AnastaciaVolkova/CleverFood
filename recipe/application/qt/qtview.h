#ifndef QTVIEW_H
#define QTVIEW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSqlQuery>
#include "ingredients_mdl.hpp"

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
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_le_recipe_name_editingFinished();

private:
    Ui::QTView *ui;
    QSqlQueryModel* model_recipes_;
    IngredientsModel* model_ingredients_;
    QItemSelectionModel* recipes_selection_model_;
    QSqlDatabase db;
    QString current_recipe_;
    QString select_recipes_list_;
};
#endif // QTVIEW_H
