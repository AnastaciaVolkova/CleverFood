#ifndef QTVIEW_H
#define QTVIEW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class QTView; }
QT_END_NAMESPACE

class QTView : public QMainWindow
{
    Q_OBJECT

public:
    QTView(const QApplication* app, QWidget *parent = nullptr);
    ~QTView();
    void onSelectionChanged(const QItemSelection &selected);
    void onSelectionIngredientsChanged(const QItemSelection &selected);
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
    void onFocusChanged ( QWidget * old, QWidget * now );

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_le_recipe_name_editingFinished();

    void on_btn_delete_pressed();

    void on_le_new_recipe_name_editingFinished();

private:
    Ui::QTView *ui;
    QSqlQueryModel* model_recipes_;
    QSqlRelationalTableModel* model_ingredients_;
    QItemSelectionModel* recipes_selection_model_;
    QSqlDatabase db;
    QString current_recipe_;
    QString select_recipes_list_;
    int previous_row_;
    void AddEmptyRowToIngredients(std::string name="");
    void DeleteEmptyRowFromIngredients();
};

#endif // QTVIEW_H
